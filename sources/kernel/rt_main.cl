
#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
#include "rt_host_structs.h"
#include "prototypes.cl"
#include "color_utils.cl"

#include "stack.cl"
#include "utils.cl"
#include "render_utils.cl"
#include "math_utils.cl"
#include "ray_trianlge_intersection.cl"
#include "simple_object.cl"
#include "ray_aabb_intersection.cl"
#include "intersection_utils.cl"
#include "unlimited_object.cl"

#include "skybox.cl"
#include "texture.cl"
#include "texture_utils.cl"

# ifdef RENDER_RAYTRACE
#  include "raytrace.cl"
#  include "light_computing.cl"
# endif

# ifdef RENDER_PATHTRACE
#  include "pathtrace.cl"
#  include "shade_pathtrace.cl"
#  include "texture_shade_pathtrace.cl"
#  include "pathtrace_utils.cl"
# endif

# ifdef RENDER_MESH
#  include "mesh_render_utils.cl"
#  include "mesh_intersection.cl"
#  include "kd_tree_traversal.cl"
# endif

__kernel void	rt_main(
    __global const t_scene *scene,
    __global const t_object *objects,
    __global const t_light *lights,
    __global const t_render_params *params,

	__global const t_kd_info *kd_info,
	__global const t_kd_arr_tree *kd_tree,
	__global const int *kd_indices,
	__global const t_mesh_info *meshes_info,
    __global const t_polygon *polygons,
	__global const float3 *vertices,
	__global const float3 *v_normals,
	__global const float3 *v_textures,

    __global const t_texture_info *texture_info,
	__global const int *texture_list,
	__global const t_skybox_info *skybox_info,
	__global const float3 *skybox_list,

    __global int *img_data,

    __global float3 *img_data_float) //img data float must always be last
{
	int3		img_point = (int3)(get_global_id(0), get_global_id(1), 0);
	int			g_id = img_point.x + img_point.y * WIN_WIDTH;

	t_ray		ray = get_ray(convert_float3(img_point), &scene->camera);

	float3		final_color = 0;
	float3		new_color = 0;
	float		seed = params->seed;

#ifdef RENDER_PATHTRACE
	float3		prev_color = img_data_float[g_id];
	new_color = pathtrace(scene, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, v_textures,
		params, texture_info, texture_list, skybox_list, skybox_info, ray, params->pathtrace_params.max_depth, &seed, /*(float2)(21.1f, 13.f)*/(float2)(img_point.x + 1, img_point.y + 1));
	final_color = mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num);
	img_data_float[g_id] = final_color;
#endif // RENDER_PATHTRACE

#ifdef RENDER_RAYTRACE
	final_color = raytrace(scene, objects, lights, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, v_textures, params, texture_info, texture_list, skybox_list, skybox_info, ray);
#endif // RENDER_RAYTRACE
	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));
}
