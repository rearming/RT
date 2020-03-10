
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
#include "closest_intersection.cl"
#include "unlimited_object.cl"

#include "skybox.cl"
#include "texture.cl"
#include "texture_utils.cl"

# ifdef RENDER_MESH
#  include "mesh_render_utils.cl"
#  include "mesh_intersection.cl"
#  include "kd_tree_traversal.cl"
# endif

__kernel void		kernel_find_intersections(
	__global const t_scene * restrict scene,
#ifdef RENDER_OBJECTS
	__global const t_object * restrict objects,
#endif
#ifdef RENDER_MESH
	__global const t_kd_info * restrict kd_info,
	__global const t_kd_arr_tree * restrict kd_tree,
	__global const int * restrict kd_indices,
	__global const t_mesh_info * restrict meshes_info,
    __global const t_polygon * restrict polygons,
	__global const float3 * restrict vertices,
	__global const float3 * restrict v_normals,
#endif
	__global const t_ray * restrict rays_buffer,
	__global const int * restrict pixel_indices,

	__global int * restrict material_hit_obj_indices,
	__global int * restrict material_hit_polygon_indices,
	__global int * restrict new_material_pixel_indices,
	__global t_rayhit * restrict material_rays_hit_buffer,
	__global uint * restrict material_buffers_len,

	__global int * restrict texture_hit_obj_indices,
	__global int * restrict texture_hit_polygon_indices,
	__global int * restrict new_textures_pixel_indices,
	__global t_rayhit * restrict texture_rays_hit_buffer,
	__global uint * restrict texture_buffers_len,

	__global int * restrict skybox_hit_pixel_indices,
	__global t_ray * restrict skybox_hit_rays_buffer,
	__global uint * restrict skybox_hit_buffers_len)
{
#ifndef RENDER_MESH
	__global const t_kd_info *kd_info = 0;
	__global const t_kd_arr_tree *kd_tree = 0;
	__global const int *kd_indices = 0;
	__global const t_mesh_info *meshes_info = 0;
	__global const t_polygon *polygons = 0;
	__global const float3 *vertices = 0;
	__global const float3 *v_normals = 0;
#endif
	int			g_id = get_global_id(0);
	int 		pixel_index = pixel_indices[g_id];

	t_ray 		ray = rays_buffer[pixel_index];

	t_rayhit	best_hit = (t_rayhit){0, INFINITY, 0};
	int			closest_obj_index = NOT_SET;
	int			closest_polygon_index = NOT_SET;

	closest_intersection(scene, objects, kd_info, kd_tree, kd_indices,
			polygons, vertices, v_normals, &ray, &best_hit, &closest_polygon_index, &closest_obj_index);

	if (isset(closest_obj_index))
	{
		if (objects[closest_obj_index].material.texture_number >= 0)
		{
			uint cached_buffer_len = atomic_inc(texture_buffers_len);

			texture_hit_obj_indices[cached_buffer_len] = closest_obj_index;
			texture_hit_polygon_indices[cached_buffer_len] = closest_polygon_index;
			new_textures_pixel_indices[cached_buffer_len] = pixel_index;
			texture_rays_hit_buffer[cached_buffer_len] = best_hit;
		}
		else // объект без текстуры
		{
			uint cached_buffer_len = atomic_inc(material_buffers_len);

			material_hit_obj_indices[cached_buffer_len] = closest_obj_index;
			material_hit_polygon_indices[cached_buffer_len] = closest_polygon_index;
			new_material_pixel_indices[cached_buffer_len] = pixel_index;
			material_rays_hit_buffer[cached_buffer_len] = best_hit;
		}
	}
	else if (isset(closest_polygon_index))
	{
		t_material	polygon_material = get_polygon_material(meshes_info, polygons, closest_polygon_index);

		if (polygon_material.texture_number >= 0)
		{
			uint cached_buffer_len = atomic_inc(texture_buffers_len);

			texture_hit_obj_indices[cached_buffer_len] = closest_obj_index;
			texture_hit_polygon_indices[cached_buffer_len] = closest_polygon_index;
			new_textures_pixel_indices[cached_buffer_len] = pixel_index;
			texture_rays_hit_buffer[cached_buffer_len] = best_hit;
		}
		else // объект без текстуры
		{
			uint cached_buffer_len = atomic_inc(material_buffers_len);

			material_hit_obj_indices[cached_buffer_len] = closest_obj_index;
			material_hit_polygon_indices[cached_buffer_len] = closest_polygon_index;
			new_material_pixel_indices[cached_buffer_len] = pixel_index;
			material_rays_hit_buffer[cached_buffer_len] = best_hit;
		}
	}
	else // луч промахнулся, запускаем скайбокс
	{
		uint cached_buffer_len = atomic_inc(skybox_hit_buffers_len);

		skybox_hit_pixel_indices[cached_buffer_len] = pixel_index;
		skybox_hit_rays_buffer[cached_buffer_len] = rays_buffer[pixel_index];
	}
}