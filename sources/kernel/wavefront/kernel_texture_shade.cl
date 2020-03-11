
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"

#include "math_utils.cl"
#include "utils.cl"
#include "mesh_render_utils.cl"

#include "texture_shade_pathtrace.cl"
#include "pathtrace_utils.cl"
#include "shade_pathtrace.cl"

#include "texture.cl"
#include "texture_utils.cl"

__kernel void		kernel_texture_shade(
		__global const t_renderer_params *params,

		__global const t_object *objects,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,

		__global const t_texture_info *texture_info,
		__global const float *texture_list,

		__global const float *raytrace_light_intensity_buffer,
		__global const int *texture_hit_obj_indices,
		__global const int *texture_hit_polygon_indices,
		__global const int *texture_pixel_indices,
		__global const t_rayhit *texture_rays_hit_buffer,

		__global const t_ray *prev_rays_buffer,

		__global t_ray *out_rays_buffer, //общий для всех буфер лучей
		__global int *out_rays_pixel_indices,
		__global uint *out_rays_buffer_len, // offset для записи новых лучей в texture_shade

		__global float3 *temp_float3_img_data)
{
	int			g_id = get_global_id(0);
	int3		img_point = get_img_point(g_id);
	float2		pixel_seed = (float2)(img_point.x, img_point.y);

	int			pixel_index = texture_pixel_indices[g_id];
	t_ray		new_ray = prev_rays_buffer[pixel_index];
	t_rayhit	best_hit = texture_rays_hit_buffer[g_id];

	t_material	material = isset(texture_hit_obj_indices[g_id])
			? objects[texture_hit_obj_indices[g_id]].material
			: get_polygon_material(meshes_info, polygons, texture_hit_polygon_indices[g_id]);

	float seed = params->seed;

	temp_float3_img_data[pixel_index] += new_ray.energy
#ifdef RENDER_RAYTRACE
		* raytrace_light_intensity_buffer[g_id]
		* shade_raytrace(&new_ray, &best_hit, &material); // texture shade raytrace
#endif
#ifdef RENDER_PATHTRACE
		* texture_shade_pathtrace(texture_info, texture_list, &objects[texture_hit_obj_indices[g_id]],
				&new_ray, &best_hit, &material, &seed, pixel_seed); //может надо будет подумать над seed'ом рандома
#endif
	if (ray_has_energy(&new_ray))
	{
		uint cached_buffer_len = atomic_inc(out_rays_buffer_len);
		out_rays_pixel_indices[cached_buffer_len] = pixel_index;
		out_rays_buffer[pixel_index] = new_ray;
	}
}
