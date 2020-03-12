
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"
#include "color_utils.cl"

#include "shade_raytrace.cl"
#include "light_computing.cl"

#include "stack.cl"
#include "utils.cl"
#include "render_utils.cl"
#include "math_utils.cl"
#include "ray_trianlge_intersection.cl"
#include "simple_object.cl"
#include "ray_aabb_intersection.cl"
#include "closest_intersection.cl"
#include "unlimited_object.cl"

#include "mesh_render_utils.cl"
#include "mesh_intersection.cl"
#include "kd_tree_traversal.cl"

float				anti_aliasing_compute_shadows(
	__global const t_scene *scene,
	__global const t_light *lights,
	__global const t_object *objects,
	__global const t_kd_info *kd_info,
	__global const t_kd_arr_tree *kd_tree,
	__global const int *kd_indices,
	__global const t_mesh_info *meshes_info,
	__global const t_polygon *polygons,
	__global const float3 *vertices,
	__global const float3 *v_normals,
	t_rayhit *hit,
	t_material *hit_material)
{
	float		intensity = 0.0f;

	if (hit_material->transmittance > 0.0f)
		return 0.0f;
	for (int i = 0; i < scene->lights_nbr; ++i)
	{
		float3		light_dir = 0;
		t_ray		shadow_ray;

		if (lights[i].type == AMBIENT)
		{
			intensity = lights[i].intensity;
			continue;
		}
		else if (lights[i].type == POINT)
			light_dir = lights[i].pos - hit->pos;
		else if (lights[i].type == DIRECTIONAL)
			light_dir = lights[i].dir;

		shadow_ray.origin = hit->pos;
		shadow_ray.dir = light_dir;
		if (in_shadow(scene, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, &shadow_ray, lights[i].type))
			continue;
		intensity += lights[i].intensity;
	}
	return intensity;
}

__kernel void		kernel_anti_aliasing_img_generation(
		__global const t_renderer_params *params,
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_light *lights,

		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		__global const float3 *v_textures,

		__global const t_texture_info *texture_info,
		__global const float *texture_list,

		__global int *img_data)
{
	int			g_id = get_global_id(0);
	int3		img_point = get_img_point(g_id);
	t_ray		ray = get_ray(convert_float3(img_point), &scene->camera);

	float3		result_color = (float3)(0);
	t_rayhit	best_hit;
	int			closest_obj_index;
	int			closest_polygon_index;

	for (int i = 0; i < params->raytrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0.0f), INFINITY, (float3)(0.0f)};
		closest_intersection(scene, objects, kd_info, kd_tree, kd_indices,
				polygons, vertices, v_normals, &ray, &best_hit, &closest_polygon_index, &closest_obj_index);

		t_material	hit_material;
		if (get_hit_material(&hit_material, objects, meshes_info, polygons, closest_obj_index, closest_polygon_index))
		{
			result_color += ray.energy
#ifdef RENDER_RAYTRACE
				* anti_aliasing_compute_shadows(scene, lights, objects,
						kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, &best_hit, &hit_material)
#endif
				* shade_raytrace(&ray, &best_hit, &hit_material);
		}
		else
		{
			result_color += ray.energy * get_float3_color(COL_BG);
			ray.energy = 0.0f;
		}
		if (!ray_has_energy(&ray))
			break;
	}
	img_data[g_id] = get_int_color(result_color);
}