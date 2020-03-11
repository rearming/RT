#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_kd_tree.h"
#include "rt_math_utils.h"

void		rt_set_kernel_args(cl_kernel kernel, int args_num, ...)
{
	va_list		args;
	int			err = CL_SUCCESS;
	enum e_cl_mem_types arg_type;
	va_start(args, args_num);

	for (int i = 0; i < args_num; ++i)
	{
		arg_type = va_arg(args, enum e_cl_mem_types);
		err |= clSetKernelArg(kernel, i, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[arg_type].mem);
	}
	va_end(args);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
}

float kernel_generate_primary_rays(t_rt *rt, cl_kernel kernel)
{
	int				err = CL_SUCCESS;
	const size_t	kernel_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};
	float	exec_time = 0;

	rt_set_kernel_args(kernel, 3, RT_CL_MEM_CAMERA, RT_CL_MEM_RAYS_BUFFER, RT_CL_MEM_PIXEL_INDICES);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("ray generation kernel");
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

void 		kernel_generate_rays_aa_pathtrace()
{
//	err = clEnqueueNDRangeKernel(g_opencl.queue,
//			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void 		kernel_generate_rays_aa_raytrace()
{
//	err = clEnqueueNDRangeKernel(g_opencl.queue,
//			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

enum e_cl_mem_types		switch_ray_buffers(int iteration)
{
	return iteration % 2 == 0 ? RT_CL_MEM_RAYS_BUFFER : RT_CL_MEM_OUT_RAYS_BUFFER;
}

float kernel_find_intersections(t_rt *rt,
								cl_kernel kernel,
								size_t kernel_work_size,
								t_kernel_work_sizes *out_work_sizes,
								int iteration)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	rt_set_kernel_args(kernel, 24, RT_CL_MEM_SCENE, RT_CL_MEM_OBJECTS,
			RT_CL_MEM_KD_INFO, RT_CL_MEM_KD_TREE, RT_CL_MEM_KD_INDICES,
			RT_CL_MEM_MESH_INFO, RT_CL_MEM_POLYGONS, RT_CL_MEM_VERTICES,
			RT_CL_MEM_V_NORMALS, switch_ray_buffers(iteration), RT_CL_MEM_PIXEL_INDICES,
			RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES, RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES,
			RT_CL_MEM_MATERIAL_PIXEL_INDICES, RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER,
			RT_CL_MEM_MATERIAL_BUFFERS_LEN, RT_CL_MEM_TEXTURE_HIT_OBJ_INDICES,
			RT_CL_MEM_TEXTURE_HIT_POLYGON_INDICES, RT_CL_MEM_TEXTURE_PIXEL_INDICES,
			RT_CL_MEM_TEXTURE_RAYS_HIT_BUFFER, RT_CL_MEM_TEXTURE_BUFFERS_LEN,
			RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES, RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER,
			RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN);

	if (rt->renderer_flags & RENDER_MESH)
	{ }

	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("find intersection kernel");

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->materials, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->textures, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->skybox, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

float kernel_raytrace_material_compute_light(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	if (kernel_work_size <= 0)
		return 0;

	rt_set_kernel_args(kernel, 16, RT_CL_MEM_SCENE,
			RT_CL_MEM_LIGHTS, RT_CL_MEM_OBJECTS, RT_CL_MEM_KD_INFO, RT_CL_MEM_KD_TREE,
			RT_CL_MEM_KD_INDICES, RT_CL_MEM_MESH_INFO, RT_CL_MEM_POLYGONS, RT_CL_MEM_VERTICES,
			RT_CL_MEM_V_NORMALS, RT_CL_MEM_RAYS_BUFFER, RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES,
			RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES, RT_CL_MEM_MATERIAL_PIXEL_INDICES,
			RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER, RT_CL_MEM_LIGHT_INTENSITY_BUFFER);

	if (rt->renderer_flags & RENDER_MESH)
	{ }

	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("raytrace compute light kernel");
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

float kernel_material_shade(t_rt *rt,
							cl_kernel kernel,
							size_t kernel_work_size,
							uint32_t *out_new_rays_buffer_len,
							int iteration)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	if (kernel_work_size <= 0)
		return exec_time;

	rt_set_kernel_args(kernel, 14, RT_CL_MEM_RENDERER_PARAMS,
			RT_CL_MEM_OBJECTS, RT_CL_MEM_MESH_INFO, RT_CL_MEM_POLYGONS,
			RT_CL_MEM_LIGHT_INTENSITY_BUFFER, RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES,
			RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES, RT_CL_MEM_MATERIAL_PIXEL_INDICES,
			RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER,
			switch_ray_buffers(iteration), switch_ray_buffers(iteration + 1), // IN and OUT rays buffers
			RT_CL_MEM_PIXEL_INDICES,
			RT_CL_MEM_OUT_RAYS_BUFFER_LEN, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("material shade kernel");

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_OUT_RAYS_BUFFER_LEN].mem,
			CL_TRUE, 0, sizeof(cl_uint), out_new_rays_buffer_len, 0, NULL, NULL); //тут когда текстуры включены можно не читать значение
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

float kernel_texture_shade(t_rt *rt,
						   cl_kernel kernel,
						   size_t kernel_work_size,
						   uint32_t *out_new_rays_buffer_len,
						   int iteration)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	if (kernel_work_size <= 0)
		return exec_time;
	rt_set_kernel_args(kernel, 16, RT_CL_MEM_RENDERER_PARAMS,
			RT_CL_MEM_OBJECTS, RT_CL_MEM_MESH_INFO, RT_CL_MEM_POLYGONS,
			RT_CL_MEM_TEXTURE_INFO, RT_CL_MEM_TEXTURE_LIST,
			RT_CL_MEM_LIGHT_INTENSITY_BUFFER, RT_CL_MEM_TEXTURE_HIT_OBJ_INDICES,
			RT_CL_MEM_TEXTURE_HIT_POLYGON_INDICES, RT_CL_MEM_TEXTURE_PIXEL_INDICES,
			RT_CL_MEM_TEXTURE_RAYS_HIT_BUFFER,
			switch_ray_buffers(iteration), switch_ray_buffers(iteration + 1), // IN and OUT rays buffers
			RT_CL_MEM_PIXEL_INDICES,
			RT_CL_MEM_OUT_RAYS_BUFFER_LEN, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("texture shade kernel");

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_OUT_RAYS_BUFFER_LEN].mem,
			CL_TRUE, 0, sizeof(cl_uint), out_new_rays_buffer_len, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

float kernel_skybox_shade(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	if (kernel_work_size <= 0)
		return exec_time;

	rt_set_kernel_args(kernel, 5,
			RT_CL_MEM_TEXTURE_INFO, RT_CL_MEM_TEXTURE_LIST,
			RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES,
			RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER,
			RT_CL_MEM_TEMP_FLOAT3_IMG_DATA);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("skybox shade kernel");
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

float kernel_fill_img_data(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	if (kernel_work_size <= 0)
		return exec_time;

	rt_set_kernel_args(kernel, 4, RT_CL_MEM_RENDERER_PARAMS, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA,
			RT_CL_MEM_MAIN_FLOAT3_IMG_DATA, RT_CL_MEM_INT_IMG);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("fill img data kernel");

	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

const struct s_kernels_info	g_kernels_info[] = {
		(struct s_kernels_info){
			.kernel_path = "sources/kernel/wavefront/kernel_generate_primary_rays.cl",
			.kernel_name = "kernel_generate_primary_rays"},
		(struct s_kernels_info){
			.kernel_path = "sources/kernel/wavefront/kernel_find_intersections.cl",
			.kernel_name = "kernel_find_intersections"
		},
		(struct s_kernels_info){
			.kernel_path = "sources/kernel/wavefront/kernel_raytrace_material_compute_light.cl",
			.kernel_name = "kernel_raytrace_material_compute_light"
		},
		(struct s_kernels_info){
			.kernel_path = "sources/kernel/wavefront/kernel_material_shade.cl",
			.kernel_name = "kernel_material_shade"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_texture_shade.cl",
				.kernel_name = "kernel_texture_shade"
		},
		(struct s_kernels_info){
			.kernel_path = "sources/kernel/wavefront/kernel_skybox_shade.cl",
			.kernel_name = "kernel_skybox_shade"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_fill_img_data.cl",
				.kernel_name = "kernel_fill_img_data"
		}
};

cl_kernel	*g_wavefront_kernels;

void		wavefront_compile_kernels(uint32_t render_flags, t_renderer_params *params)
{
	size_t					i;
	size_t					kernels_num = sizeof(g_kernels_info) / sizeof(struct s_kernels_info);

	rt_init_renderer_params(params);
	i = 0;
	g_wavefront_kernels = rt_safe_malloc(sizeof(cl_kernel) * kernels_num);
	while (i < kernels_num)
	{
		printf("compiling [%s]\n", g_kernels_info[i].kernel_name);
		rt_opencl_create_kernel(
				g_kernels_info[i].kernel_path,
				g_kernels_info[i].kernel_name,
				rt_get_kernel_compile_options(render_flags),
				&g_wavefront_kernels[i]);
		i++;
	}
}

void		bzero_buffer(enum e_cl_mem_types mem_index)
{
	int			err = CL_SUCCESS;
	cl_uint		zero = 0;

	err |= clEnqueueWriteBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[mem_index].mem,
			CL_TRUE, 0, sizeof(cl_uint), &zero, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_FILL_BUFFER, err);
}

void		bzero_float3_temp_img(cl_float3 *zero_arr)
{
	int			err = CL_SUCCESS;

	err |= clEnqueueWriteBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEMP_FLOAT3_IMG_DATA].mem,
			CL_TRUE, 0, sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT, zero_arr, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_FILL_BUFFER, err);
}

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

	rt_wavefront_setup_buffers(rt, params); //todo params вообще-то в разных рендерерах разные хранятся, потом переделать
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

	for (int i = 0; i < 26; ++i)
	{
		if (g_opencl.wavefront_shared_buffers[i].copy_mem == true)
			clReleaseMemObject(g_opencl.wavefront_shared_buffers[i].mem);
	}
	if (rt_camera_moved(&rt->scene.camera))
		params.pathtrace_params.current_samples_num = 1;
	first_init_done = true;
}