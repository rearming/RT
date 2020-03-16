#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"

t_opencl_mem_obj	rt_check_opencl_memobj(t_opencl_mem_obj mem_obj)
{
	t_opencl_mem_obj	checked_mem_obj;
	cl_char				dummy_ptr;

	if (mem_obj.ptr != NULL || !(mem_obj.mem_flags & CL_MEM_COPY_HOST_PTR))
		return mem_obj;
	checked_mem_obj.ptr = &dummy_ptr;
	checked_mem_obj.mem_flags = RT_DEFAULT_MEM_FLAG;
	checked_mem_obj.render_state = mem_obj.render_state; // todo what must be here ?
	checked_mem_obj.size = sizeof(cl_char);
	return (checked_mem_obj);
}

void		rt_opencl_prepare_memory(t_rt *rt, uint32_t render_state)
{
	t_opencl_mem_obj	opencl_mem_objs[] = {
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->scene, sizeof(t_scene), RT_DEFAULT_MEM_FLAG, STATE_CAMERA_CHANGED | STATE_LIGHTS_CHANGED | STATE_OBJECTS_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.objects, sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, STATE_OBJECTS_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.lights, sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, STATE_LIGHTS_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->params, sizeof(t_render_params), RT_DEFAULT_MEM_FLAG, STATE_PARAMS_CHANGED | STATE_PATHTRACE}),

			rt_check_opencl_memobj((t_opencl_mem_obj){&rt->kd_info, sizeof(t_kd_info), RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.tree_arr, sizeof(t_kd_arr_tree) * rt->kd_info.nodes_num, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->kd_info.indices, sizeof(cl_int) * rt->kd_info.indices_num, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.meshes_info, sizeof(t_mesh_info) * rt->scene.meshes.num_meshes, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.polygons, sizeof(t_polygon) * rt->scene.meshes.num_polygons, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.vertices, sizeof(cl_float3) * rt->scene.meshes.num_vertices, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.v_normals, sizeof(cl_float3) * rt->scene.meshes.num_v_normals, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){rt->scene.meshes.v_textures, sizeof(cl_float3) * rt->scene.meshes.num_v_textures, RT_DEFAULT_MEM_FLAG, STATE_MESH_CHANGED}),

			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_info, sizeof(t_texture_info) * g_textures.texture_info_size, RT_DEFAULT_MEM_FLAG, STATE_TEXTURES_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.texture_list, sizeof(cl_int) * g_textures.texture_list_size, RT_DEFAULT_MEM_FLAG, STATE_TEXTURES_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.skybox_info, sizeof(t_skybox_info), RT_DEFAULT_MEM_FLAG, STATE_SKYBOX_CHANGED}),
			rt_check_opencl_memobj((t_opencl_mem_obj){g_textures.skybox_list, sizeof(cl_float3) * g_textures.skybox_info->size, RT_DEFAULT_MEM_FLAG, STATE_SKYBOX_CHANGED}),

			rt_check_opencl_memobj((t_opencl_mem_obj){NULL, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT, CL_MEM_READ_WRITE, STATE_EXIT})
	};
	g_opencl.buffers_num = sizeof(opencl_mem_objs) / sizeof(t_opencl_mem_obj);
	rt_opencl_alloc_buffers(render_state, opencl_mem_objs);
}
