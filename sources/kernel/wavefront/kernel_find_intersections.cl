
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
	__global int *material_buffers_len

	__global __write_only t_rayhit *rays_hit_buffer,
	//нужен для продления в shade, один для обычных и текстурных материалов
	__global __write_only int *new_pixel_indices,
	//индексы пикселей тоже общие
	__global int *shared_buffers_len,
	// нужна длинна буферов лучей и индексов пикселей

/// по сути будут еще такие же буферы для пересечений с текстурными объектами
//	__global __write_only int *texture_hit_obj_indices,
//	__global __write_only int *texture_hit_polygon_indices,
//	__global int *texture_buffers_len
	)
{
	int		g_id = get_global_id(0);
	int3	img_point = get_img_point(g_id);

	t_ray 		ray = rays_buffer[prev_pixel_indices[g_id]];

	t_rayhit	best_hit;
	int			closest_obj_index = NOT_SET;
	int			closest_polygon_index = NOT_SET;

	closest_intersection(scene, objects, kd_info, kd_tree, kd_indices,
			polygons, vertices, v_normals, &ray, &best_hit,
			&closest_polygon_index, &closest_obj_index);
	if (isset(closest_obj_index) || isset(closest_polygon_index))
	{
		hit_obj_indices[*buffers_len] = closest_obj_index;
		hit_polygon_indices[*buffers_len] = closest_polygon_index;
		rays_hit_buffer[*buffers_len] = best_hit;
		new_pixel_indices[*buffers_len] = prev_pixel_indices[g_id];
		atomic_inc(buffers_len);
	} //todo в другом случае запускать shade skybox
}