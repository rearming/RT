#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "rt_wavefront_render.h"

float kernel_generate_primary_rays(t_rt *rt, cl_kernel kernel)
{
	int				err = CL_SUCCESS;
	const size_t	kernel_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};
	float	exec_time = 0;

	rt_set_kernel_args(kernel, 4, RT_CL_MEM_CAMERA,
			RT_CL_MEM_PRIMARY_RAYS_BUFFER, RT_CL_MEM_PRIMARY_PIXEL_INDICES,
			RT_CL_MEM_NUM_PIXEL_RAYS_BUFFER);

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

float kernel_find_intersections(t_rt *rt,
								cl_kernel kernel,
								size_t kernel_work_size,
								t_kernel_work_sizes *out_work_sizes,
								int iteration)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	rt_set_kernel_args(kernel, 25, RT_CL_MEM_SCENE, RT_CL_MEM_OBJECTS,
			RT_CL_MEM_KD_INFO, RT_CL_MEM_KD_TREE, RT_CL_MEM_KD_INDICES,
			RT_CL_MEM_MESH_INFO, RT_CL_MEM_POLYGONS, RT_CL_MEM_VERTICES,
			RT_CL_MEM_V_NORMALS,
			switch_ray_buffers(iteration),
			iteration == 0 ? RT_CL_MEM_PRIMARY_PIXEL_INDICES : RT_CL_MEM_PREV_PIXEL_INDICES,
			RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES, RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES,
			RT_CL_MEM_MATERIAL_PIXEL_INDICES, RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER,
			RT_CL_MEM_MATERIAL_RAYS_BUFFER, RT_CL_MEM_MATERIAL_BUFFERS_LEN,
			RT_CL_MEM_TEXTURE_HIT_OBJ_INDICES,
			RT_CL_MEM_TEXTURE_HIT_POLYGON_INDICES, RT_CL_MEM_TEXTURE_PIXEL_INDICES,
			RT_CL_MEM_TEXTURE_RAYS_HIT_BUFFER, RT_CL_MEM_TEXTURE_BUFFERS_LEN,
			RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES, RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER,
			RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN);

	if (rt->render_settings & RENDER_MESH)
	{ }

	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("find intersection kernel");

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_MATERIAL_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->materials, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_TEXTURE_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->textures, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN].mem, CL_TRUE, 0, sizeof(cl_uint), &out_work_sizes->skybox, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}

float kernel_raytrace_material_compute_light(t_rt *rt,
											 cl_kernel kernel,
											 size_t kernel_work_size,
											 int iteration)
{
	int				err = CL_SUCCESS;
	float exec_time = 0;

	if (kernel_work_size <= 0)
		return 0;

	rt_set_kernel_args(kernel, 16, RT_CL_MEM_SCENE,
			RT_CL_MEM_LIGHTS, RT_CL_MEM_OBJECTS, RT_CL_MEM_KD_INFO, RT_CL_MEM_KD_TREE,
			RT_CL_MEM_KD_INDICES, RT_CL_MEM_MESH_INFO, RT_CL_MEM_POLYGONS, RT_CL_MEM_VERTICES,
			RT_CL_MEM_V_NORMALS,
			iteration == 0 ? RT_CL_MEM_PRIMARY_RAYS_BUFFER : RT_CL_MEM_PREV_RAYS_BUFFER,
			RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES,
			RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES, RT_CL_MEM_MATERIAL_PIXEL_INDICES,
			RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER, RT_CL_MEM_LIGHT_INTENSITY_BUFFER);

	if (rt->render_settings & RENDER_MESH)
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
			RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER, RT_CL_MEM_MATERIAL_RAYS_BUFFER,
			RT_CL_MEM_OUT_RAYS_BUFFER,
			RT_CL_MEM_PREV_PIXEL_INDICES, // по факту out pixel indices?
			RT_CL_MEM_OUT_RAYS_BUFFER_LEN, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("material shade kernel");

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_OUT_RAYS_BUFFER_LEN].mem,
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
			RT_CL_MEM_PREV_PIXEL_INDICES,
			RT_CL_MEM_OUT_RAYS_BUFFER_LEN, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("texture shade kernel");

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_OUT_RAYS_BUFFER_LEN].mem,
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

	rt_set_kernel_args(kernel, 5, RT_CL_MEM_RENDERER_PARAMS, RT_CL_MEM_TEMP_FLOAT3_IMG_DATA,
			RT_CL_MEM_MAIN_FLOAT3_IMG_DATA, RT_CL_MEM_NUM_PIXEL_RAYS_BUFFER, RT_CL_MEM_INT_IMG);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &kernel_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info("fill img data kernel");

	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.wf_shared_buffers[RT_CL_MEM_INT_IMG].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	exec_time = rt_get_kernel_exec_time();
	clReleaseEvent(g_opencl.profile_event);
	return exec_time;
}
