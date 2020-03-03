
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

__kernel void		kernel_find_intersections(
	__global __read_only const t_scene *scene,
#ifdef RENDER_OBJECTS
	__global __read_only const t_object *objects,
#endif
#ifdef RENDER_MESH
	__global __read_only const t_kd_info *kd_info,
	__global __read_only const t_kd_arr_tree *kd_tree,
	__global __read_only const int *kd_indices,
	__global __read_only const t_mesh_info *meshes_info,
    __global __read_only const t_polygon *polygons,
	__global __read_only const float3 *vertices,
	__global __read_only const float3 *v_normals,
#endif
	__global __read_only const t_ray *rays_buffer,
	__global __read_only const int *prev_pixel_indices,

	__global __write_only int *material_hit_obj_indices,
	__global __write_only int *material_hit_polygon_indices,
	__global __write_only int *new_material_pixel_indices,
	__global __write_only t_rayhit *material_rays_hit_buffer,
	__global uint *material_buffers_len,

	__global __write_only int *texture_hit_obj_indices,
	__global __write_only int *texture_hit_polygon_indices,
	__global __write_only int *new_textures_pixel_indices,
	__global __write_only t_rayhit *texture_rays_hit_buffer,
	__global uint *texture_buffers_len,

	__global __write_only int *skybox_hit_pixel_indices,
	__global __write_only t_ray *skybox_hit_rays_buffer,
	__global uint *skybox_hit_buffers_len,

	__global __write_only int *img_data //test img buf
	)
{
#ifndef RENDER_MESH
	__global __read_only const t_kd_info *kd_info = 0;
	__global __read_only const t_kd_arr_tree *kd_tree = 0;
	__global __read_only const int *kd_indices = 0;
	__global __read_only const t_mesh_info *meshes_info = 0;
	__global __read_only const t_polygon *polygons = 0;
	__global __read_only const float3 *vertices = 0;
	__global __read_only const float3 *v_normals = 0;
#endif
	int		g_id = get_global_id(0);
	int3	img_point = get_img_point(g_id);

	t_ray 		ray = rays_buffer[prev_pixel_indices[g_id]];

	t_rayhit	best_hit = (t_rayhit){0, INFINITY, 0};
	int			closest_obj_index = NOT_SET;
	int			closest_polygon_index = NOT_SET;

	closest_intersection(scene, objects, kd_info, kd_tree, kd_indices,
			polygons, vertices, v_normals, &ray, &best_hit, &closest_polygon_index, &closest_obj_index);

	if (closest_obj_index != NOT_SET)
	{
		img_data[g_id] = get_int_color(objects[closest_obj_index].material.diffuse);
		if (objects[closest_obj_index].material.texture_number >= 0)
		{
			texture_hit_obj_indices[*texture_buffers_len] = closest_obj_index;
			new_textures_pixel_indices[*texture_buffers_len] = closest_obj_index;
			texture_rays_hit_buffer[*texture_buffers_len] = best_hit;
			atomic_inc(texture_buffers_len);
		}
		else // объект без текстуры
		{
			material_hit_obj_indices[*material_buffers_len] = closest_obj_index;
			new_material_pixel_indices[*material_buffers_len] = prev_pixel_indices[g_id];
			material_rays_hit_buffer[*material_buffers_len] = best_hit;
			atomic_inc(material_buffers_len);
		}
	}
	else if (isset(closest_polygon_index))
	{
		t_material	polygon_material = get_polygon_material(meshes_info, polygons, closest_polygon_index);

		img_data[g_id] = get_int_color(polygon_material.diffuse);
		if (polygon_material.texture_number >= 0)
		{
			texture_hit_obj_indices[*texture_buffers_len] = closest_polygon_index;
			new_textures_pixel_indices[*texture_buffers_len] = closest_polygon_index;
			texture_rays_hit_buffer[*texture_buffers_len] = best_hit;
			atomic_inc(texture_buffers_len);
		}
		else // объект без текстуры
		{
			material_hit_obj_indices[*material_buffers_len] = closest_polygon_index;
			new_material_pixel_indices[*material_buffers_len] = prev_pixel_indices[g_id];
			material_rays_hit_buffer[*material_buffers_len] = best_hit;
			atomic_inc(material_buffers_len);
		}
	}
	else // луч промахнулся, запускаем скайбокс
	{
		img_data[g_id] = COL_GREY;
		skybox_hit_pixel_indices[*skybox_hit_buffers_len] = prev_pixel_indices[g_id];
		skybox_hit_rays_buffer[*skybox_hit_buffers_len] = rays_buffer[g_id];
		atomic_inc(skybox_hit_buffers_len);
	}
}