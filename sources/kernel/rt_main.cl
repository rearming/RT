
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"
#include "color_utils.cl"

#include "stack.cl"
#include "utils.cl"
#include "render_utils.cl"
#include "math_utils.cl"
#include "ray_trianlge_intersection.cl"
#include "simple_object.cl"
#include "ray_aabb_intersection.cl"
//#include "simple_object_intersections.cl"
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
    __global __read_only const t_scene *scene,
#ifdef RENDER_OBJECTS
    __global __read_only const t_object *objects,
#endif
	__global __read_only const t_light *lights,
    __global __read_only const t_renderer_params *params,
#ifdef RENDER_MESH
	__global __read_only const t_kd_info *kd_info,
	__global __read_only const t_kd_arr_tree *kd_tree,
	__global __read_only const int *kd_indices,
	__global __read_only const t_mesh_info *meshes_info,
    __global __read_only const t_polygon *polygons,
	__global __read_only const float3 *vertices,
	__global __read_only const float3 *v_normals,
# ifdef RENDER_MESH_VTEXTURES
	__global __read_only const float3 *v_textures,
# endif
#endif
#ifdef RENDER_PATHTRACE
    __global float3 *img_data_float,
#endif
#ifdef RENDER_TEXTURES
    __global __read_only const t_texture_info *texture_info,
	__global __read_only const float *texture_list,
#endif
    __global __write_only int *img_data,
    __global __read_only t_ray *rays)
{
	int3		img_point = (int3)(get_global_id(0), get_global_id(1), 0);
	int			g_id = img_point.x + img_point.y * WIN_WIDTH;

	float3		final_color = 0;
	float3		new_color = 0;
	float		seed = params->seed;

#ifndef RENDER_OBJECTS
	__global const t_object			*objects = 0;
#endif
#ifndef RENDER_MESH
 	__global const t_mesh_info		*meshes_info = 0;
 	__global const t_polygon		*polygons = 0;
 	__global const float3			*vertices = 0;
 	__global const float3 			*v_normals = 0;
 	__global const t_kd_info		*kd_info = 0;
	__global const t_kd_arr_tree	*kd_tree = 0;
	__global const int				*kd_indices = 0;
#endif
#ifndef RENDER_MESH_VTEXTURES
 	__global const float3			*v_textures = 0;
#endif
#ifndef RENDER_TEXTURES
 	__global const t_texture_info 	*texture_info;
	__global const float 			*texture_list;
#endif

#ifdef RENDER_PATHTRACE
	float3		prev_color = img_data_float[g_id];

	t_ray ray = rays[RAYS_CHUNK_SIZE * g_id + 0];
#ifdef RENDER_ANTI_ALIASING
	if (ray.energy.x > 0)
	{
		for	(int i = 0; i < RAYS_CHUNK_SIZE; i++)
		{
			t_ray ray = rays[RAYS_CHUNK_SIZE * g_id + i];
			if (ray.energy.x <= 0)
				continue;

			float3 temp_color = pathtrace(scene, objects, kd_info, kd_tree, kd_indices,
					meshes_info, polygons, vertices, v_normals, v_textures,
					params, texture_info, texture_list, ray,
					params->pathtrace_params.max_depth, &seed, /*(float2)(21.1f, 13.f)*/(float2)(img_point.x + 1, img_point.y + 1));
			new_color = mix_avg_colors(new_color, temp_color, i);
		}
	}
	else
#endif // RENDER_ANTI_ALIASING
	{
		ray = rays[RAYS_CHUNK_SIZE * g_id + 4];
		new_color = pathtrace(scene, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, v_textures,
			params, texture_info, texture_list, ray, params->pathtrace_params.max_depth, &seed, /*(float2)(21.1f, 13.f)*/(float2)(img_point.x + 1, img_point.y + 1));
	}
	final_color = mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num);
	img_data_float[g_id] = final_color;

#endif // RENDER_PATHTRACE

#ifdef RENDER_RAYTRACE
	t_ray ray = rays[RAYS_CHUNK_SIZE * g_id + 0];

#ifdef RENDER_ANTI_ALIASING
	if (ray.energy.x > 0)
	{
		for	(int i = 0; i < RAYS_CHUNK_SIZE; i++)
		{
			ray = rays[RAYS_CHUNK_SIZE * g_id + i];
			if (ray.energy.x <= 0)
				continue;
			float3 temp_color = raytrace(scene, objects, lights, kd_info, kd_tree, kd_indices,
					meshes_info, polygons, vertices, v_normals, v_textures, params, texture_info, texture_list, ray);
			final_color = mix_avg_colors(final_color, temp_color, i);
		}
	}
	else
#endif // RENDER_ANTI_ALIASING
	{
		ray = rays[RAYS_CHUNK_SIZE * g_id + 4];
		final_color = raytrace(scene, objects, lights, kd_info, kd_tree, kd_indices,
					meshes_info, polygons, vertices, v_normals, v_textures, params, texture_info, texture_list, ray);
	}

#endif // RENDER_RAYTRACE
	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));
}
