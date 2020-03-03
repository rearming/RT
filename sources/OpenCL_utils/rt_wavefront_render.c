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

void 		kernel_generate_primary_rays(t_rt *rt, cl_program program, cl_kernel kernel)
{
	int				err = CL_SUCCESS;
	const size_t	global_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};

	err |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_CAMERA]);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RAYS_BUFFER]);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_PIXEL_INDICES]); // todo можно сделать в цикле va_arg'ом (передавать
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
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

void 		kernel_find_intersections(t_rt *rt, cl_program program, cl_kernel kernel, size_t *global_work_size, size_t out_global_work_size)
{
	int				err = CL_SUCCESS;

	err |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SCENE]);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_OBJECTS]);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_INFO]);
	err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_TREE]);
	err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_KD_INDICES]);
	err |= clSetKernelArg(kernel, 5, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MESH_INFO]);
	err |= clSetKernelArg(kernel, 6, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_POLYGONS]);
	err |= clSetKernelArg(kernel, 7, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_VERTICES]);
	err |= clSetKernelArg(kernel, 8, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_V_NORMALS]);

	err |= clSetKernelArg(kernel, 9, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_RAYS_BUFFER]);
	err |= clSetKernelArg(kernel, 10, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_PIXEL_INDICES]);

	err |= clSetKernelArg(kernel, 11, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES]);
	err |= clSetKernelArg(kernel, 12, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES]);
	err |= clSetKernelArg(kernel, 13, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_PIXEL_INDICES]);
	err |= clSetKernelArg(kernel, 14, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER]);
	err |= clSetKernelArg(kernel, 15, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_MATERIAL_BUFFERS_LEN]);

	err |= clSetKernelArg(kernel, 16, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_HIT_OBJ_INDICES]);
	err |= clSetKernelArg(kernel, 17, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_HIT_POLYGON_INDICES]);
	err |= clSetKernelArg(kernel, 18, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_PIXEL_INDICES]);
	err |= clSetKernelArg(kernel, 19, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_RAYS_HIT_BUFFER]);
	err |= clSetKernelArg(kernel, 20, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEXTURE_BUFFERS_LEN]);

	err |= clSetKernelArg(kernel, 21, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES]);
	err |= clSetKernelArg(kernel, 22, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER]);
	err |= clSetKernelArg(kernel, 23, sizeof(cl_mem), &g_opencl.wavefront_shared_buffers[RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN]);

	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);

	err = clEnqueueReadBuffer(g_opencl.queue, buffers_len, CL_TRUE, 0, sizeof(int), &out_global_work_size, 0, NULL, NULL);
	// todo тут будут читаться materials_buffer_len, texture_buffer_len и skybox_buffer_len
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void 		kernel_shade_and_generate_new_rays(t_rt *rt, cl_program program, cl_kernel kernel, size_t global_work_size)
{
	int		err;

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
}

void 		kernel_fill_img_mix_colors()
{
//	err = clEnqueueNDRangeKernel(g_opencl.queue,
//			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void		rt_setup_wavefront_shared_buffers(t_rt *rt)
{
	const int	memobj_num = 25;

	rt_wavefront_render_prepare_shared_memory(rt, memobj_num,
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.camera, sizeof(t_camera), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}), //todo лучей может быть больше пикселей в случае с АА
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene, sizeof(t_scene), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.objects, sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, false, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->kd_info, sizeof(t_kd_info), RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->kd_info.tree_arr, sizeof(t_kd_arr_tree) * rt->kd_info.nodes_num, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->kd_info.indices, sizeof(cl_int) * rt->kd_info.indices_num, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.meshes.meshes_info, sizeof(t_mesh_info) * rt->scene.meshes.num_meshes, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.meshes.polygons, sizeof(t_polygon) * rt->scene.meshes.num_polygons, false, RT_DEFAULT_MEM_FLAG, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.meshes.vertices, sizeof(cl_float3) * rt->scene.meshes.num_vertices, false, RT_DEFAULT_MEM_FLAG, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene.meshes.v_normals, sizeof(cl_float3) * rt->scene.meshes.num_v_normals, false, RT_DEFAULT_MEM_FLAG, RENDER_MESH}),

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}), // material hit buffers
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_rayhit) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int), false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}), // texture hit buffers
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_rayhit) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int), false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}), // skybox hit buffers
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(t_ray) * WIN_WIDTH * WIN_HEIGHT, false, CL_MEM_READ_WRITE, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int), false, CL_MEM_READ_WRITE, RENDER_ALWAYS})
			);
}

void 		render_wavefront(void *rt_ptr)
{
	t_rt	*rt = rt_ptr;


	cl_program	generate_primary_rays_program;
	cl_kernel	generate_primary_rays_kernel;

	rt_opencl_create_kernel(
			"sources/kernel/wavefront/kernel_generate_primary_rays.cl",
			"kernel_generate_primary_rays",
			rt_get_kernel_compile_options(RENDER_NOTHING),
			&generate_primary_rays_kernel,
			&generate_primary_rays_program);

	kernel_generate_primary_rays(rt_ptr, generate_primary_rays_program, generate_primary_rays_kernel);
	// OUT_BUFFERS -> 1) rays_buffer 2) pixel_indices 3) buffers_len

	cl_program	find_intersection_program;
	cl_kernel	find_intersection_kernel;

	rt_opencl_create_kernel(
			"sources/kernel/wavefront/kernel_find_intersections.cl",
			"kernel_find_intersections",
			rt_get_kernel_compile_options(rt->renderer_flags),
			&find_intersection_kernel,
			&find_intersection_program);

	size_t		new_kernel_num = 0;

	kernel_find_intersections(rt, find_intersection_program, find_intersection_kernel, (size_t[1]){WIN_WIDTH * WIN_HEIGHT}, new_kernel_num);
//	IN_BUFFERS <- 1) rays_buffer 2) pixel_indices 3) buffers_len
//	OUT_BUFFERS -> 1) obj_indices 2) polygon_indices 3) ray_hits (normal, position) 4) pixel_indices 5) buffer_len

	cl_program	shade_generate_new_rays_program;
	cl_kernel	shade_generate_new_rays_kernel;

	rt_opencl_create_kernel(
			"sources/kernel/wavefront/kernel_shade_generate_new_rays.cl",
			"kernel_shade_generate_new_rays",
			rt_get_kernel_compile_options(rt->renderer_flags),
			&shade_generate_new_rays_kernel,
			&shade_generate_new_rays_program);

	kernel_shade_and_generate_new_rays(rt, shade_generate_new_rays_program, shade_generate_new_rays_kernel, new_kernel_num);

// 	IN_BUFFERS <- 1) obj_indices 2) polygon_indices 3) ray_hits (normal, position) 4) pixel_indices 5) buffer_len
//	OUT_BUFFERS -> 1) rays_buffer 2) pixel_indices 3) buffers_len 4) float3 colors buffer (pathtrace) 5) img (write into img)

// 	goto -> kernel_find_intersection

//	kernel_fill_img_mix_colors(); // IN_BUFFERS <- 1) struct {float3 color, int pixel_index} | OUT_BUFFERS -> int *pixels

	printf("wavefront render done\n");
}