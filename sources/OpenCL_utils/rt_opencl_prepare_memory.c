#include "rt.h"
#include "rt_opencl.h"

t_opencl_mem_obj	rt_check_opencl_memobj(t_opencl_mem_obj mem_obj)
{
	t_opencl_mem_obj	checked_mem_obj;
	cl_char				dummy_ptr;

	if (mem_obj.ptr != NULL)
		return mem_obj;
	checked_mem_obj.ptr = &dummy_ptr;
	checked_mem_obj.copy = false;
	checked_mem_obj.mem_flags = RT_DEFAULT_MEM_FLAG;
	checked_mem_obj.renderer_flags = mem_obj.renderer_flags;
	checked_mem_obj.size = sizeof(cl_char);
	return (checked_mem_obj);
}

void		rt_opencl_prepare_memory(t_rt *rt, t_rt_renderer *renderer)
{
	const int		max_memobj_number = 15;

	rt_opencl_move_host_mem_to_kernel(renderer, max_memobj_number,
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene,
				sizeof(t_scene), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.objects,
				sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, false, RENDER_OBJECTS}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.lights,
				sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, false, RENDER_RAYTRACE}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&renderer->params,
				sizeof(t_renderer_params), RT_DEFAULT_MEM_FLAG, true, RENDER_ALWAYS}),

			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->kd_info,
				sizeof(t_kd_info), RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.tree_arr,
				sizeof(t_kd_arr_tree) * rt->kd_info.nodes_num, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.indices,
				sizeof(cl_int) * rt->kd_info.indices_num, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),

			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.meshes_info,
				sizeof(t_mesh_info) * rt->scene.meshes.num_meshes, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.polygons,
				sizeof(t_polygon) * rt->scene.meshes.num_polygons, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.vertices,
				sizeof(cl_float3) * rt->scene.meshes.num_vertices, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.v_normals,
				sizeof(cl_float3) * rt->scene.meshes.num_v_normals, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.v_textures,
				sizeof(cl_float3) * rt->scene.meshes.num_v_textures, RT_DEFAULT_MEM_FLAG, false, RENDER_MESH_VTEXTURES}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&g_img_data_float,
				sizeof(cl_float3) * WIN_HEIGHT * WIN_WIDTH, RT_MEM_RW_FLAG, false, RENDER_PATHTRACE}),
			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_info,
				sizeof(t_texture_info) * g_textures.texture_info_size, RT_DEFAULT_MEM_FLAG, false, RENDER_TEXTURES}),
			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_list,
				sizeof(cl_float) * g_textures.texture_list_size, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, false, RENDER_TEXTURES})

	);
}
