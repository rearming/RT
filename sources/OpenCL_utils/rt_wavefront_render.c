#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_kd_tree.h"

cl_mem	camera_mem;
cl_mem	rays_buffer;
cl_mem	pixel_indices;

cl_mem	scene_mem;
cl_mem	objects_mem;
cl_mem	kd_info_mem;
cl_mem	kd_tree_mem;
cl_mem	kd_indices_mem;
cl_mem	mesh_info_mem;
cl_mem	polygons_mem;
cl_mem	vertices_mem;
cl_mem	v_normals_mem;

cl_mem	new_pixel_indices;
cl_mem	hit_obj_indices;
cl_mem	hit_polygon_indices;
cl_mem	rays_hit_buffer;
cl_mem	buffers_len;

void 		kernel_generate_primary_rays(t_rt *rt, cl_program program, cl_kernel kernel)
{
	int				err;
	const size_t	global_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};

	camera_mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_camera), &rt->scene.camera, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	rays_buffer = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE, sizeof(t_ray) * WIN_WIDTH * WIN_HEIGHT, NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	pixel_indices = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE, sizeof(int) * WIN_WIDTH * WIN_HEIGHT, NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &camera_mem);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &rays_buffer);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &pixel_indices);
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
	int				err;

	scene_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(t_scene), &rt->scene, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	objects_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(t_object) * rt->scene.obj_nbr, rt->scene.objects, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	kd_info_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(t_kd_info), &rt->kd_info, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	kd_tree_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(t_kd_arr_tree) * rt->kd_info.nodes_num, rt->kd_info.tree_arr, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	kd_indices_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(cl_int) * rt->kd_info.indices_num, rt->kd_info.indices, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	mesh_info_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(t_mesh_info) * rt->scene.meshes.num_meshes, rt->scene.meshes.meshes_info, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	polygons_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(t_polygon) * rt->scene.meshes.num_polygons, rt->scene.meshes.polygons, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	vertices_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(cl_float3) * rt->scene.meshes.num_vertices, rt->scene.meshes.vertices, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	v_normals_mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG, sizeof(cl_float3) * rt->scene.meshes.num_v_normals, rt->scene.meshes.v_normals, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);

	err |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &scene_mem);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &objects_mem);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &kd_info_mem);
	err |= clSetKernelArg(kernel, 3, sizeof(cl_mem), &kd_tree_mem);
	err |= clSetKernelArg(kernel, 4, sizeof(cl_mem), &kd_indices_mem);
	err |= clSetKernelArg(kernel, 5, sizeof(cl_mem), &mesh_info_mem);
	err |= clSetKernelArg(kernel, 6, sizeof(cl_mem), &polygons_mem);
	err |= clSetKernelArg(kernel, 7, sizeof(cl_mem), &vertices_mem);
	err |= clSetKernelArg(kernel, 8, sizeof(cl_mem), &v_normals_mem);
	err |= clSetKernelArg(kernel, 9, sizeof(cl_mem), &rays_buffer);
	err |= clSetKernelArg(kernel, 10, sizeof(cl_mem), &pixel_indices);
	err |= clSetKernelArg(kernel, 11, sizeof(cl_mem), &hit_obj_indices);
	err |= clSetKernelArg(kernel, 12, sizeof(cl_mem), &hit_polygon_indices);
	err |= clSetKernelArg(kernel, 13, sizeof(cl_mem), &rays_hit_buffer);
	err |= clSetKernelArg(kernel, 14, sizeof(cl_mem), &new_pixel_indices);
	err |= clSetKernelArg(kernel, 15, sizeof(cl_mem), &buffers_len);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);

	err = clEnqueueReadBuffer(g_opencl.queue, buffers_len, CL_TRUE, 0, sizeof(int), &out_global_work_size, 0, NULL, NULL);
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