#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_math_utils.h"
#include "rt_wavefront_render.h"

cl_kernel	*g_wavefront_kernels;

void 		render_wavefront(void *rt_ptr)
{
	t_rt						*rt = rt_ptr;
	static t_renderer_params	params;
	static bool					first_init_done = false;
	t_kernel_work_sizes			kernel_work_sizes;
	uint32_t					find_intersection_new_work_size;
	static cl_float3			*float3_temp_img_zeros;

	static float avg_exec_time = 0;
	float	total_exec_time = 0;

	float	raygen_exec = 0;
	float	intersect_exec = 0;
	float	light_exec = 0;
	float	material_shade_exec = 0;
	float	texture_shade_exec = 0;
	float	skybox_shade_exec = 0;
	float	img_fill_exec = 0;

	if (!first_init_done)
	{
		wavefront_compile_kernels(rt->renderer_flags, &params);
		float3_temp_img_zeros = rt_safe_malloc(sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT);
		for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
			float3_temp_img_zeros[i] = (cl_float3){{0, 0, 0}};
	}

	rt_wavefront_setup_buffers(rt, params, WIN_WIDTH * WIN_HEIGHT); //todo params вообще-то в разных рендерерах разные хранятся, потом переделать
	bzero_float3_temp_img(float3_temp_img_zeros); // обнулить temp_float3_img_data
	raygen_exec += kernel_generate_primary_rays(rt_ptr, g_wavefront_kernels[RT_KERNEL_GENERATE_PRIMARY_RAYS]);

	find_intersection_new_work_size = WIN_WIDTH * WIN_HEIGHT; // потом тут будет кол-во лучей после генерации анти-алиасингом

	for (int j = 0; j < 8; ++j)
	{
		if (find_intersection_new_work_size <= 0)
			break;
		bzero_buffer(RT_CL_MEM_MATERIAL_BUFFERS_LEN);
		bzero_buffer(RT_CL_MEM_TEXTURE_BUFFERS_LEN);
		bzero_buffer(RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN);
		intersect_exec += kernel_find_intersections(rt, g_wavefront_kernels[RT_KERNEL_FIND_INTERSECTIONS], find_intersection_new_work_size, &kernel_work_sizes, j);

		if (rt->events.info)
			printf("kernel new work sizes: material: [%u], texture: [%u], skybox: [%u]\n",
					kernel_work_sizes.materials, kernel_work_sizes.textures, kernel_work_sizes.skybox);

		if (rt->renderer_flags & RENDER_RAYTRACE)
			light_exec += kernel_raytrace_material_compute_light(rt, g_wavefront_kernels[RT_KERNEL_MATERIAL_COMPUTE_LIGHT], kernel_work_sizes.materials);

		find_intersection_new_work_size = 0;
		bzero_buffer(RT_CL_MEM_OUT_RAYS_BUFFER_LEN);
		material_shade_exec += kernel_material_shade(rt, g_wavefront_kernels[RT_KERNEL_MATERIAL_SHADE], kernel_work_sizes.materials, &find_intersection_new_work_size, j);
		texture_shade_exec += kernel_texture_shade(rt, g_wavefront_kernels[RT_KERNEL_TEXTURE_SHADE], kernel_work_sizes.textures, &find_intersection_new_work_size, j);

		if (rt->events.info)
			printf("find_intersection new work size: [%u]\n", find_intersection_new_work_size);

		skybox_shade_exec += kernel_skybox_shade(rt, g_wavefront_kernels[RT_KERNEL_SKYBOX_SHADE], kernel_work_sizes.skybox);

		if (rt->events.info)
			printf("wavefront render [%i] iteration\n\n", j);
	}

	img_fill_exec += kernel_fill_img_data(rt, g_wavefront_kernels[RT_KERNEL_FILL_IMG_DATA], WIN_WIDTH * WIN_HEIGHT);

	params.pathtrace_params.current_samples_num++;
	params.seed = drand48();

	printf("ray gen exec time: [%.3f]\n", raygen_exec);
	printf("find intersection exec time: [%.3f]\n", intersect_exec);
	if (rt->renderer_flags & RENDER_RAYTRACE)
		printf("light shadow exec time: [%.3f]\n", light_exec);
	printf("material shade exec time: [%.3f]\n", material_shade_exec);
	if (rt->renderer_flags & RENDER_TEXTURES)
		printf("texture shade exec time: [%.3f]\n", texture_shade_exec);
	printf("skybox shade exec time: [%.3f]\n", skybox_shade_exec);
	printf("img fill exec time: [%.3f]\n", img_fill_exec);
	total_exec_time = raygen_exec + intersect_exec + light_exec + material_shade_exec + skybox_shade_exec + img_fill_exec;
	printf("total exec time: [%f]\n", total_exec_time);
	avg_exec_time = rt_lerpf(avg_exec_time, total_exec_time, 1.0f / params.pathtrace_params.current_samples_num);
	printf("average exec time: [%f]\n", avg_exec_time);
	printf("current samples num: [%i]\n", params.pathtrace_params.current_samples_num);
	printf("\n");

	for (int i = 0; i < 37; ++i)
	{
		if (g_opencl.wavefront_shared_buffers[i].copy_mem == true)
			clReleaseMemObject(g_opencl.wavefront_shared_buffers[i].mem);
	}
	if (rt_camera_moved(&rt->scene.camera))
		params.pathtrace_params.current_samples_num = 1;
	first_init_done = true;
}