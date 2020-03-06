#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_kd_tree.h"

void		rt_set_kernel_args(int args_num, ...)
{
	va_list		args;

	va_start(args, args_num);

	va_end(args);
}

void kernel_generate_primary_rays(t_rt *rt, cl_kernel kernel)
{
	int				err = CL_SUCCESS;
	const size_t	kernel_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};

	err |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_CAMERA].mem);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RAYS_BUFFER].mem);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_PIXEL_INDICES].mem); // todo можно сделать в цикле va_arg'ом (передавать
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

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

int		*test_enque_buffer(t_cl_mem_types enum_val)
{
	int err;

	int			*test_data = rt_safe_malloc(sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[enum_val].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			test_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	return test_data;
}

void kernel_find_intersections(t_rt *rt,
							   cl_kernel kernel,
							   size_t kernel_work_size,
							   t_kernel_work_sizes *out_work_sizes)
{
	int				err = CL_SUCCESS;
	int				arg_num = 0;

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SCENE].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_OBJECTS].mem);

	if (rt->renderer_flags & RENDER_MESH)
	{
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_INFO].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_TREE].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_INDICES].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MESH_INFO].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_POLYGONS].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_VERTICES].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_V_NORMALS].mem);
	}

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RAYS_BUFFER].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_PIXEL_INDICES].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_PIXEL_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_BUFFERS_LEN].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_HIT_OBJ_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_HIT_POLYGON_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_PIXEL_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_RAYS_HIT_BUFFER].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_BUFFERS_LEN].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem);

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

	err |= clEnqueueReadBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void	kernel_raytrace_material_compute_light(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	int				arg_num = 0;

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SCENE].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_LIGHTS].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_OBJECTS].mem);

	if (rt->renderer_flags & RENDER_MESH)
	{
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_INFO].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_TREE].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_INDICES].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MESH_INFO].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_POLYGONS].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_VERTICES].mem);
		err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_V_NORMALS].mem);
	}

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RAYS_BUFFER].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_PIXEL_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_LIGHT_INTENSITY_BUFFER].mem);

	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("raytrace compute light kernel");
	clReleaseEvent(g_opencl.profile_event);
}

void kernel_material_shade(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	int				arg_num = 0;

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RENDERER_PARAMS].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_OBJECTS].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MESH_INFO].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_POLYGONS].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_LIGHT_INTENSITY_BUFFER].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_PIXEL_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RAYS_BUFFER].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_OUT_RAYS_BUFFER].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_OUT_RAYS_PIXEL_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_OUT_RAYS_BUFFER_LEN].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEMP_FLOAT3_IMG_DATA].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("material shade kernel");
	clReleaseEvent(g_opencl.profile_event);
}

void kernel_shade_textures(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int		err;

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
}

void kernel_skybox_shade(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	int				arg_num = 0;

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEMP_FLOAT3_IMG_DATA].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("skybox shade kernel");
	clReleaseEvent(g_opencl.profile_event);

	err |= clEnqueueReadBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void 		kernel_material_fill_img_data(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	int				arg_num = 0;

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_PIXEL_INDICES].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RENDERER_PARAMS].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEMP_FLOAT3_IMG_DATA].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MAIN_FLOAT3_IMG_DATA].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("material fill img data kernel");
	clReleaseEvent(g_opencl.profile_event);
}

void 		kernel_texture_fill_img_data(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	int				arg_num = 0;

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_PIXEL_INDICES].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RENDERER_PARAMS].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEMP_FLOAT3_IMG_DATA].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MAIN_FLOAT3_IMG_DATA].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("texture fill img data kernel");
	clReleaseEvent(g_opencl.profile_event);
}

void 		kernel_skybox_fill_img_data(t_rt *rt, cl_kernel kernel, size_t kernel_work_size)
{
	int				err = CL_SUCCESS;
	int				arg_num = 0;

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES].mem);

	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RENDERER_PARAMS].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEMP_FLOAT3_IMG_DATA].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MAIN_FLOAT3_IMG_DATA].mem);
	err |= clSetKernelArg(kernel, arg_num++, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("skybox fill img data kernel");
	clReleaseEvent(g_opencl.profile_event);
}

void 		render_wavefront(void *rt_ptr)
{
	t_rt *rt = rt_ptr;
	static bool kernels_compiled = false;

	t_renderer_params	params;

	rt_init_renderer_params(&params);

	rt_wavefront_setup_buffers(rt, params); //todo params вообще-то в разных рендерерах разные хранятся, потом переделать

	static cl_program generate_primary_rays_program;
	static cl_kernel generate_primary_rays_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_generate_primary_rays.cl",
				"kernel_generate_primary_rays",
				rt_get_kernel_compile_options(RENDER_NOTHING),
				&generate_primary_rays_kernel,
				&generate_primary_rays_program);
	}

	kernel_generate_primary_rays(rt_ptr, generate_primary_rays_kernel);

	static cl_program	find_intersection_program;
	static cl_kernel	find_intersection_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_find_intersections.cl",
				"kernel_find_intersections",
				rt_get_kernel_compile_options(rt->renderer_flags),
				&find_intersection_kernel,
				&find_intersection_program);
	}

	t_kernel_work_sizes		kernel_work_sizes;

	kernel_find_intersections(rt,
			find_intersection_kernel, WIN_WIDTH * WIN_HEIGHT,
			&kernel_work_sizes);

//	printf("kernel new work sizes: material: [%u], texture: [%u], skybox: [%u]\n",
//			kernel_work_sizes.materials, kernel_work_sizes.textures, kernel_work_sizes.skybox);

	static cl_program	raytrace_material_compute_light_program;
	static cl_kernel	raytrace_material_compute_light_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_raytrace_material_compute_light.cl",
				"kernel_raytrace_material_compute_light",
				rt_get_kernel_compile_options(rt->renderer_flags),
				&raytrace_material_compute_light_kernel,
				&raytrace_material_compute_light_program);
	}

	if (kernel_work_sizes.materials > 0)
	{
		kernel_raytrace_material_compute_light(rt,
				raytrace_material_compute_light_kernel,
				kernel_work_sizes.materials);
	}

	static cl_program	material_shade_program;
	static cl_kernel	material_shade_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_material_shade.cl",
				"kernel_material_shade",
				rt_get_kernel_compile_options(rt->renderer_flags),
				&material_shade_kernel,
				&material_shade_program);
	}

	if (kernel_work_sizes.materials > 0)
	{
		kernel_material_shade(rt,
				material_shade_kernel, kernel_work_sizes.materials);
	}

	static cl_program	skybox_shade_program;
	static cl_kernel	skybox_shade_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_skybox_shade.cl",
				"kernel_skybox_shade",
				rt_get_kernel_compile_options(rt->renderer_flags),
				&skybox_shade_kernel,
				&skybox_shade_program);
	}

	if (kernel_work_sizes.skybox > 0)
	{
		kernel_skybox_shade(rt, skybox_shade_kernel, kernel_work_sizes.skybox);
	}

// 	goto -> kernel_find_intersection

	static cl_program	material_fill_img_data_program;
	static cl_kernel	material_fill_img_data_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_material_fill_img_data.cl",
				"kernel_material_fill_img_data",
				rt_get_kernel_compile_options(rt->renderer_flags),
				&material_fill_img_data_kernel,
				&material_fill_img_data_program);
	}

	if (kernel_work_sizes.materials > 0)
		kernel_material_fill_img_data(rt, material_fill_img_data_kernel, kernel_work_sizes.materials);

	static cl_program	texture_fill_img_data_program;
	static cl_kernel	texture_fill_img_data_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_texture_fill_img_data.cl",
				"kernel_texture_fill_img_data",
				rt_get_kernel_compile_options(rt->renderer_flags),
				&texture_fill_img_data_kernel,
				&texture_fill_img_data_program);
	}

	if (kernel_work_sizes.textures > 0)
		kernel_texture_fill_img_data(rt, material_fill_img_data_kernel, kernel_work_sizes.textures);

	static cl_program	skybox_fill_img_data_program;
	static cl_kernel	skybox_fill_img_data_kernel;

	if (!kernels_compiled)
	{
		rt_opencl_create_kernel(
				"sources/kernel/wavefront/kernel_skybox_fill_img_data.cl",
				"kernel_skybox_fill_img_data",
				rt_get_kernel_compile_options(rt->renderer_flags),
				&skybox_fill_img_data_kernel,
				&skybox_fill_img_data_program);
	}

	if (kernel_work_sizes.skybox > 0)
		kernel_skybox_fill_img_data(rt, material_fill_img_data_kernel, kernel_work_sizes.skybox);

	int err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[RT_CL_MEM_INT_IMG].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);

	printf("wavefront render done\n");
	for (int i = 0; i < 26; ++i)
	{
		if (g_opencl.wavefront_shared_buffers[i].copy_mem == true)
			clReleaseMemObject(g_opencl.wavefront_shared_buffers[i].mem);
	}
	kernels_compiled = true;
}