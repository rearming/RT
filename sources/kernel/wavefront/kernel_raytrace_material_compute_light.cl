
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

#include "light_computing.cl"

//# ifdef RENDER_MESH
#  include "mesh_render_utils.cl"
#  include "mesh_intersection.cl"
#  include "kd_tree_traversal.cl"
//# endif

__kernel void		kernel_raytrace_material_compute_light(
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
		__global const t_ray *rays_buffer,

		__global const int *material_hit_obj_indices,
		__global const int *material_hit_polygon_indices,
		__global const int *material_pixel_indices,
		__global const t_rayhit *material_rays_hit_buffer,

		__global float *out_light_intensity_buffer)
{
	int			g_id = get_global_id(0);
	t_ray 		ray = rays_buffer[material_pixel_indices[g_id]];
	t_rayhit	best_hit = material_rays_hit_buffer[g_id];

	t_material	material = isset(material_hit_obj_indices[g_id])
			? objects[material_hit_obj_indices[g_id]].material
			: get_polygon_material(meshes_info, polygons, material_hit_polygon_indices[g_id]);

	float light_intensity = compute_light(scene, lights, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, &best_hit, &ray, &material);
	out_light_intensity_buffer[g_id] = light_intensity;
}
