#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_math_utils.h"
#include "rt_wavefront_render.h"

cl_kernel	*g_wavefront_kernels;

float		kernel_anti_aliasing_img_generation(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	float			exec_time = 0;

	if (kernel_work_size <= 0)
		return exec_time;

	printf("setting kernel arg img generation\n");
	rt_set_kernel_args(kernel, 15,
			RT_CL_MEM_RENDERER_PARAMS, RT_CL_MEM_SCENE, RT_CL_MEM_OBJECTS,
			RT_CL_MEM_LIGHTS, RT_CL_MEM_KD_INFO, RT_CL_MEM_KD_TREE, RT_CL_MEM_KD_INDICES,
			RT_CL_MEM_MESH_INFO, RT_CL_MEM_POLYGONS,
			RT_CL_MEM_VERTICES, RT_CL_MEM_V_NORMALS, RT_CL_MEM_V_TEXTURES,
			RT_CL_MEM_TEXTURE_INFO, RT_CL_MEM_TEXTURE_LIST, RT_CL_MEM_INT_IMG);

	printf("started kernel anti-aliasing img generation\n");
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("anti-aliasing img generation kernel");

	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

float		kernel_anti_aliasing_rays_generation(t_rt *rt, cl_kernel kernel, size_t kernel_work_size,
		uint32_t *out_find_intersection_work_size)
{
	int				err = CL_SUCCESS;
	float			exec_time = 0;

	if (kernel_work_size <= 0)
		return exec_time;
	rt_set_kernel_args(kernel, 5,
			RT_CL_MEM_CAMERA, RT_CL_MEM_INT_IMG,
			RT_CL_MEM_PRIMARY_RAYS_BUFFER, RT_CL_MEM_PRIMARY_PIXEL_INDICES,
			RT_CL_MEM_PRIMARY_RAYS_BUFFER_LEN);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("anti-aliasing rays generation kernel");

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_PRIMARY_RAYS_BUFFER_LEN].mem,
			CL_TRUE, 0, sizeof(cl_uint), out_find_intersection_work_size, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);

	printf("find_intersection new work size: [%u]\n", *out_find_intersection_work_size);
//	test_sobel_processing(kernel, *out_find_intersection_work_size);
	return exec_time;
}

void 		render_wavefront(void *rt_ptr)
{
	t_rt						*rt = rt_ptr;
	static t_renderer_params	params;
	t_kernel_work_sizes			kernel_work_sizes;
	uint32_t					find_intersection_new_work_size;
	static uint32_t				cached_find_intersection_work_size;
	static cl_float3			*float3_temp_img_zeros;

	static float avg_exec_time = 0;
	float	total_exec_time = 0;

	float	aa_img_gen_exec = 0;
	float	aa_raygen_exec = 0;

	float	raygen_exec = 0;
	float	intersect_exec = 0;
	float	light_exec = 0;
	float	material_shade_exec = 0;
	float	texture_shade_exec = 0;
	float	skybox_shade_exec = 0;
	float	img_fill_exec = 0;

	printf("\nstart wavefront render!\n");
	if (rt->render_state == STATE_ALL)
	{
		rt->render_settings |= RENDER_ANTI_ALIASING;
		wavefront_compile_kernels(rt->render_settings, &params);
		float3_temp_img_zeros = rt_safe_malloc(sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT);
		for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
			float3_temp_img_zeros[i] = (cl_float3){{0, 0, 0}};
	}
	else
		wavefront_release_buffers(rt->render_state);

	find_intersection_new_work_size = cached_find_intersection_work_size;

	if (rt->render_state & STATE_CAMERA_CHANGED)
		params.pathtrace_params.current_samples_num = 1;
	if (rt->render_settings & RENDER_ANTI_ALIASING && (rt->render_state & STATE_CAMERA_CHANGED))
	{
		if (rt->render_state != STATE_ALL)
			wavefront_release_buffers(STATE_AA_RAYS_GENERATED);
		wavefront_setup_buffers(rt, params, (rt->render_state & ~(STATE_AA_RAYS_GENERATED)), 0);
		bzero_buffer(RT_CL_MEM_PRIMARY_RAYS_BUFFER_LEN);
		aa_img_gen_exec += kernel_anti_aliasing_img_generation(rt,
				g_wavefront_kernels[RT_KERNEL_ANTI_ALIASING_IMG_GEN], WIN_WIDTH * WIN_HEIGHT);
		aa_raygen_exec += kernel_anti_aliasing_rays_generation(rt,
				g_wavefront_kernels[RT_KERNEL_ANTI_ALIASING_RAYS_GEN], WIN_WIDTH * WIN_HEIGHT, &find_intersection_new_work_size);
		printf("anti-aliasing img generation exec time: [%f]\n", aa_img_gen_exec);
		printf("anti-aliasing ray generation exec time: [%f]\n", aa_raygen_exec);
		cached_find_intersection_work_size = find_intersection_new_work_size;
		printf("find intesect size: [%i], cached size: [%i]\n", find_intersection_new_work_size, cached_find_intersection_work_size);
		rt->render_state &= STATE_NOTHING;
		rt->render_state |= STATE_AA_RAYS_GENERATED;
	}
	else
		find_intersection_new_work_size = WIN_WIDTH * WIN_HEIGHT;

	wavefront_setup_buffers(rt, params, rt->render_state, find_intersection_new_work_size);

	bzero_float3_temp_img(float3_temp_img_zeros); // обнулить temp_float3_img_data

	if (!(rt->render_settings & RENDER_ANTI_ALIASING) && rt->render_state & STATE_CAMERA_CHANGED)
	{
		bzero_buffer(RT_CL_MEM_PRIMARY_RAYS_BUFFER_LEN);
		raygen_exec += kernel_generate_primary_rays(rt_ptr, g_wavefront_kernels[RT_KERNEL_GENERATE_PRIMARY_RAYS]);
	}

	for (int j = 0; j < 8; ++j)
	{
		if (find_intersection_new_work_size <= 0)
			break;
		bzero_buffer(RT_CL_MEM_MATERIAL_BUFFERS_LEN);
		bzero_buffer(RT_CL_MEM_TEXTURE_BUFFERS_LEN);
		bzero_buffer(RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN);
		intersect_exec += kernel_find_intersections(rt,
				g_wavefront_kernels[RT_KERNEL_FIND_INTERSECTIONS], find_intersection_new_work_size, &kernel_work_sizes, j);

		if (rt->events.info)
			printf("kernel new work sizes: material: [%u], texture: [%u], skybox: [%u]\n",
					kernel_work_sizes.materials, kernel_work_sizes.textures, kernel_work_sizes.skybox);

		if (rt->render_settings & RENDER_RAYTRACE)
			light_exec += kernel_raytrace_material_compute_light(rt,
					g_wavefront_kernels[RT_KERNEL_MATERIAL_COMPUTE_LIGHT],
					kernel_work_sizes.materials, 0);

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
	if (rt->render_settings & RENDER_RAYTRACE)
		printf("light shadow exec time: [%.3f]\n", light_exec);
	printf("material shade exec time: [%.3f]\n", material_shade_exec);
	if (rt->render_settings & RENDER_TEXTURES)
		printf("texture shade exec time: [%.3f]\n", texture_shade_exec);
	printf("skybox shade exec time: [%.3f]\n", skybox_shade_exec);
	printf("img fill exec time: [%.3f]\n", img_fill_exec);
	total_exec_time = raygen_exec + intersect_exec + light_exec + material_shade_exec
			+ skybox_shade_exec + img_fill_exec + aa_img_gen_exec + aa_raygen_exec;
	printf("total exec time: [%f]\n", total_exec_time);
	avg_exec_time = rt_lerpf(avg_exec_time, total_exec_time, 1.0f / (float)(params.pathtrace_params.current_samples_num - 1));
	printf("average exec time: [%f]\n", avg_exec_time);
	if (rt->render_settings & RENDER_PATHTRACE)
		printf("current samples num: [%i]\n", params.pathtrace_params.current_samples_num);
	printf("\n");

	rt->render_state = STATE_NOTHING;
	rt->render_state |= STATE_PARAMS_CHANGED; // для обновления current_samples_num
}