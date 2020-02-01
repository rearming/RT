#include "rt.h"
#include "../debug/rt_debug_utils.h"
#include "rt_math_utils.h"
#include "time.h"

void
rt_opencl_prepare_memory(t_rt *rt, cl_kernel kernel, uint32_t renderer_flags)
{
	g_opencl.opencl_memobj_number = 9;
	rt_opencl_move_host_mem_to_kernel(kernel, renderer_flags, g_opencl.opencl_memobj_number,
		(t_opencl_mem_obj){&rt->scene,
			sizeof(t_scene), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS},
		(t_opencl_mem_obj){rt->scene.objects,
			sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, false, RENDER_OBJECTS},
		(t_opencl_mem_obj){rt->scene.lights,
			sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, false, RENDER_RAYTRACE},
		(t_opencl_mem_obj){&rt->opencl_params,
			sizeof(t_opencl_params), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS},
		(t_opencl_mem_obj){rt->scene.meshes.meshes_info,
			sizeof(t_mesh_info) * rt->scene.meshes.num_meshes, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH},
		(t_opencl_mem_obj){rt->scene.meshes.polygons,
			sizeof(t_polygon) * rt->scene.meshes.num_polygons, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH},
		(t_opencl_mem_obj){rt->scene.meshes.vertices,
			sizeof(cl_float3) * rt->scene.meshes.num_vertices, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH},
		(t_opencl_mem_obj){rt->scene.meshes.v_normals,
			sizeof(cl_float3) * rt->scene.meshes.num_v_normals, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH},
		(t_opencl_mem_obj){rt->scene.meshes.v_textures,
			sizeof(cl_float3) * rt->scene.meshes.num_v_textures, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH_VTEXTURES},
		(t_opencl_mem_obj){&g_img_data_float,
			sizeof(cl_float3) * WIN_HEIGHT * WIN_WIDTH, RT_MEM_RW_FLAG, false, RENDER_PATHTRACE}
			);
}

void		rt_update_rt_params(t_rt *rt)
{
	if (rt->opencl_params.render_algo == PATH_TRACE)
	{
		rt->opencl_params.seed = drand48();
		rt->opencl_params.pathtrace_params.current_samples_num++;
	}
	else
		rt->opencl_params.pathtrace_params.current_samples_num = 0;
	if (rt_camera_moved(&rt->scene.camera))
		rt->opencl_params.pathtrace_params.current_samples_num = 0;
}

void		rt_opencl_render(t_rt *rt)
{
	const size_t	kernel_num = OPENCL_RELEASE_KERNEL_NUM;
//	const size_t	kernel_num = 50;
//	const size_t	kernel_num = 2;
	int				err;
	t_rt_renderer	*renderer;

	renderer = rt_get_renderer(rt->opencl_params.renderer_flags);
	rt_opencl_prepare_memory(rt, renderer->kernel, rt->opencl_params.renderer_flags);
	rt_opencl_setup_image_buffer(renderer->kernel);
	rt_update_rt_params(rt);
	if (rt->events.info)
		rt_print_debug_info(rt);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 1, NULL, &kernel_num, NULL, 0, NULL, &g_opencl.profile_event);
	if (rt->events.info)
		rt_print_opencl_profile_info();
	clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err |= clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	opencl_clean_memobjs(rt->opencl_params.renderer_flags);
}
