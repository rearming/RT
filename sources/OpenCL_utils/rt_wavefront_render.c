#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_kd_tree.h"

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

void kernel_generate_primary_rays(t_rt *rt, cl_kernel kernel)
{
	int				err = CL_SUCCESS;
	const size_t	kernel_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};

	rt_set_kernel_args(kernel, 3, RT_CL_MEM_CAMERA, RT_CL_MEM_RAYS_BUFFER, RT_CL_MEM_PIXEL_INDICES);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("ray generation kernel");
	clReleaseEvent(g_opencl.profile_event);
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

void kernel_find_intersections(t_rt *rt,
							   cl_kernel kernel,
							   size_t kernel_work_size,
							   t_kernel_work_sizes *out_work_sizes,
							   int iteration)
{
	int				err = CL_SUCCESS;

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
	clReleaseEvent(g_opencl.profile_event);

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->materials, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->textures, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->skybox, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void	kernel_raytrace_material_compute_light(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;

	if (kernel_work_size <= 0)
		return;

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
	clReleaseEvent(g_opencl.profile_event);
}

void	kernel_material_shade(t_rt *rt,
						   cl_kernel kernel,
						   size_t kernel_work_size,
						   uint32_t *out_new_rays_buffer_len,
						   int iteration)
{
	int				err = CL_SUCCESS;

	if (kernel_work_size <= 0)
		return;

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
	clReleaseEvent(g_opencl.profile_event);

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wavefront_shared_buffers[RT_CL_MEM_OUT_RAYS_BUFFER_LEN].mem,
			CL_TRUE, 0, sizeof(cl_uint), out_new_rays_buffer_len, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void	kernel_shade_textures(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int		err;

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
}

void	kernel_skybox_shade(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;

	if (kernel_work_size <= 0)
		return;

	rt_set_kernel_args(kernel, 3, RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES,
			RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("skybox shade kernel");
	clReleaseEvent(g_opencl.profile_event);
}

void 	kernel_fill_img_data(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;

	if (kernel_work_size <= 0)
		return;

	rt_set_kernel_args(kernel, 4, RT_CL_MEM_RENDERER_PARAMS, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA,
			RT_CL_MEM_MAIN_FLOAT3_IMG_DATA, RT_CL_MEM_INT_IMG);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("fill img data kernel");
	clReleaseEvent(g_opencl.profile_event);

	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
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

	if (!first_init_done)
	{
		wavefront_compile_kernels(rt->renderer_flags, &params);
		float3_temp_img_zeros = rt_safe_malloc(sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT);
		for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
			float3_temp_img_zeros[i] = (cl_float3){{0, 0, 0}};
	}
	rt_wavefront_setup_buffers(rt, params); //todo params вообще-то в разных рендерерах разные хранятся, потом переделать

	bzero_float3_temp_img(float3_temp_img_zeros); // обнулить temp_float3_img_data
	kernel_generate_primary_rays(rt_ptr, g_wavefront_kernels[RT_KERNEL_GENERATE_PRIMARY_RAYS]);

	find_intersection_new_work_size = WIN_WIDTH * WIN_HEIGHT; // потом тут будет кол-во лучей после генерации анти-алиасингом

	for (int j = 0; j < 8; ++j)
	{
		if (find_intersection_new_work_size <= 0)
			break;
		bzero_buffer(RT_CL_MEM_MATERIAL_BUFFERS_LEN);
		bzero_buffer(RT_CL_MEM_TEXTURE_BUFFERS_LEN);
		bzero_buffer(RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN);
		kernel_find_intersections(rt, g_wavefront_kernels[RT_KERNEL_FIND_INTERSECTIONS], find_intersection_new_work_size, &kernel_work_sizes, j);
		if (rt->events.info)
			printf("kernel new work sizes: material: [%u], texture: [%u], skybox: [%u]\n",
					kernel_work_sizes.materials, kernel_work_sizes.textures, kernel_work_sizes.skybox);

		if (rt->renderer_flags & RENDER_RAYTRACE)
			kernel_raytrace_material_compute_light(rt, g_wavefront_kernels[RT_KERNEL_MATERIAL_COMPUTE_LIGHT], kernel_work_sizes.materials);

		bzero_buffer(RT_CL_MEM_OUT_RAYS_BUFFER_LEN);
		find_intersection_new_work_size = 0;
		kernel_material_shade(rt, g_wavefront_kernels[RT_KERNEL_MATERIAL_SHADE], kernel_work_sizes.materials, &find_intersection_new_work_size, j);
		if (rt->events.info)
			printf("find_intersection new work size: [%u]\n", find_intersection_new_work_size);

		kernel_skybox_shade(rt, g_wavefront_kernels[RT_KERNEL_SKYBOX_SHADE], kernel_work_sizes.skybox);
		if (rt->events.info)
			printf("wavefront render [%i] iteration\n\n", j);
	}

	kernel_fill_img_data(rt, g_wavefront_kernels[RT_KERNEL_FILL_IMG_DATA], WIN_WIDTH * WIN_HEIGHT);

	params.pathtrace_params.current_samples_num++;
	params.seed = drand48();

	printf("current samples num: [%i]\n", params.pathtrace_params.current_samples_num);
	for (int i = 0; i < 26; ++i)
	{
		if (g_opencl.wavefront_shared_buffers[i].copy_mem == true)
			clReleaseMemObject(g_opencl.wavefront_shared_buffers[i].mem);
	}
	first_init_done = true;
}