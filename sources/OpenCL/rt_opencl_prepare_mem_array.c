#include "rt.h"
#include "rt_opencl.h"
#include "rt_window_params.h"

void		rt_opencl_prepare_mem_arr1(
		t_rt *rt,
		t_opencl_mem_obj *mem_obj)
{
	mem_obj[0] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {&rt->scene.camera, sizeof(t_camera),
								RT_DEFAULT_MEM_FLAG, ACTION_CAMERA_CHANGED});
	mem_obj[1] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {&rt->scene, sizeof(t_scene),
								RT_DEFAULT_MEM_FLAG,
								ACTION_CAMERA_CHANGED | ACTION_LIGHTS_CHANGED |
								ACTION_OBJECTS_CHANGED});
	mem_obj[2] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->scene.objects,
								rt->scene.obj_nbr * sizeof(t_object),
								RT_DEFAULT_MEM_FLAG, ACTION_OBJECTS_CHANGED});
	mem_obj[3] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->scene.lights,
								rt->scene.lights_nbr * sizeof(t_light),
								RT_DEFAULT_MEM_FLAG, ACTION_LIGHTS_CHANGED});
	mem_obj[4] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {&rt->params, sizeof(t_render_params),
								RT_DEFAULT_MEM_FLAG,
								ACTION_PARAMS_CHANGED | ACTION_PATHTRACE});
	mem_obj[5] = rt_check_opencl_memobj((t_opencl_mem_obj) {
			rt->render_state & STATE_NO_MESH ? NULL : &rt->kd_info,
			sizeof(t_kd_info), RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
}

void		rt_opencl_prepare_mem_arr2(
		t_rt *rt,
		t_opencl_mem_obj *opencl_mem_objs)
{
	opencl_mem_objs[6] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->kd_info.tree_arr,
								rt->kd_info.nodes_num * sizeof(t_kd_arr_tree),
								RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
	opencl_mem_objs[7] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->kd_info.indices,
								rt->kd_info.indices_num * sizeof(cl_int),
								RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
}

void		rt_opencl_prepare_mem_arr3(
		t_rt *rt,
		t_opencl_mem_obj *opencl_mem_objs)
{
	opencl_mem_objs[8] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->scene.meshes.meshes_info,
			sizeof(t_mesh_info) * rt->scene.meshes.num_meshes,
			RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
	opencl_mem_objs[9] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->scene.meshes.polygons, sizeof(t_polygon) *
			rt->scene.meshes.num_polygons,
			RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
	opencl_mem_objs[10] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->scene.meshes.vertices, sizeof(cl_float3) *
			rt->scene.meshes.num_vertices,
			RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
	opencl_mem_objs[11] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->scene.meshes.v_normals, sizeof(cl_float3) *
			rt->scene.meshes.num_v_normals,
			RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
	opencl_mem_objs[12] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {rt->scene.meshes.v_textures, sizeof(cl_float3) *
			rt->scene.meshes.num_v_textures,
			RT_DEFAULT_MEM_FLAG, ACTION_MESH_CHANGED});
}

void		rt_opencl_prepare_mem_arr4(
		t_rt *rt,
		t_opencl_mem_obj *opencl_mem_objs)
{
	(void)rt;
	opencl_mem_objs[13] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {g_textures.texture_info,
			sizeof(t_texture_info) * g_textures.texture_info_size,
			RT_DEFAULT_MEM_FLAG, ACTION_TEXTURES_CHANGED});
	opencl_mem_objs[14] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {g_textures.texture_list,
			g_textures.texture_list_size * sizeof(cl_int),
			RT_DEFAULT_MEM_FLAG, ACTION_TEXTURES_CHANGED});
	opencl_mem_objs[15] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {g_textures.skybox_info, sizeof(t_skybox_info),
			RT_DEFAULT_MEM_FLAG, ACTION_SKYBOX_CHANGED});
	opencl_mem_objs[16] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {g_textures.skybox_list,
			sizeof(cl_float3) * g_textures.skybox_info->size,
			RT_DEFAULT_MEM_FLAG, ACTION_SKYBOX_CHANGED});
	opencl_mem_objs[17] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {NULL, WIN_WIDTH * WIN_HEIGHT * sizeof(cl_int),
			CL_MEM_READ_WRITE, ACTION_EXIT});
}

void		rt_opencl_prepare_mem_arr5(
		t_rt *rt,
		t_opencl_mem_obj *opencl_mem_objs)
{
	(void)rt;
	opencl_mem_objs[18] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {NULL, WIN_WIDTH * WIN_HEIGHT * sizeof(cl_int),
								CL_MEM_READ_WRITE, ACTION_EXIT});
	opencl_mem_objs[19] = rt_check_opencl_memobj(
			(t_opencl_mem_obj) {NULL, WIN_WIDTH * WIN_HEIGHT * sizeof(cl_float),
								CL_MEM_READ_WRITE, ACTION_EXIT});
}
