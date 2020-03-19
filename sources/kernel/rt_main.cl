
#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_window_params.h"
#include "rt_colors.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
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
    __global float *depth_buffer,

    __global float3 *img_data_float) //img data float must always be last
{
	int			g_id = get_global_id(0);
	int3		img_point = get_img_point(g_id);

	t_ray		ray = get_ray(convert_float3(img_point), &scene->camera);

	float		seed = params->seed;
#ifndef RENDER_IMPRESSIVE
	float2		pixel_seed = convert_float2(img_point.xy);
#else
	float2		pixel_seed = (float2)(21.21f, 42.42f);
#endif

	float3		final_color = 0;
	float3		new_color = 0;
	float3		prev_color = img_data_float[g_id];
	float3		temp_color = 0;

	float		intersection_distance;

#ifdef RENDER_ANTI_ALIASING
	float	fsaa_offset = 0.5f;

	for (int y = -1; y < 2; ++y)
	{
		for (int x = -1; x < 2; ++x)
		{
			float3	ray_origin = convert_float3(img_point);
			ray_origin.x += x * fsaa_offset;
			ray_origin.y += y * fsaa_offset;
			ray = get_ray(ray_origin, &scene->camera);
#endif // RENDER_ANTI_ALIASING

#ifdef RENDER_RAYTRACE
			temp_color += raytrace(scene, objects, lights, kd_info, kd_tree, kd_indices,
					meshes_info, polygons, vertices, v_normals, v_textures,
					params, texture_info, texture_list, skybox_list, skybox_info, ray, &intersection_distance);
#endif // RENDER_RAYTRACE

#ifdef RENDER_PATHTRACE
			temp_color += pathtrace(scene, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, v_textures,
				params, texture_info, texture_list, skybox_list, skybox_info, ray,
				params->pathtrace_params.max_depth, &seed, pixel_seed, &intersection_distance);
#endif

#ifdef RENDER_ANTI_ALIASING
		}
	}
	final_color = temp_color / 9;
#else
	final_color = temp_color;
#endif // RENDER_ANTI_ALIASING

#ifdef RENDER_PATHTRACE
	final_color = mix_avg_colors(prev_color, final_color, params->pathtrace_params.current_samples_num);
	img_data_float[g_id] = final_color;
#endif

	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));
	depth_buffer[g_id] = intersection_distance;
}
