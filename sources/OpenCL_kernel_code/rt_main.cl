
#include "opencl_defines.cl"
#include "opencl_structs.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "rt_host_structs.h"
#include "prototypes.cl"
#include "color_utils.cl"

#include "utils.cl"
#include "math_utils.cl"
#include "ray_trianlge_intersection.cl"
#include "simple_object_intersections.cl"
#include "intersection_utils.cl"

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
# endif

__kernel void	rt_main(
    __global const t_scene *scene,
#ifdef RENDER_OBJECTS
    __global const t_object *objects,
#endif
#ifdef RENDER_RAYTRACE
    __global const t_light *lights,
#endif
    __global const t_renderer_params *params,
#ifdef RENDER_MESH
	__global const t_mesh_info *meshes_info,
    __global const t_polygon *polygons,
	__global const float3 *vertices,
	__global const float3 *v_normals,
# ifdef RENDER_MESH_VTEXTURES
	__global const float3 *v_textures,
# endif
#endif
#ifdef RENDER_PATHTRACE
    __global float3 *img_data_float,
#endif
    __global const t_texture_info *texture_info,
	__global const float *texture_list,
    __global int *img_data)
{
	int			g_id = get_global_id(0);
	int3		img_point = get_img_point(g_id);

	t_ray		ray = get_ray(convert_float3(img_point), &scene->camera);

	float3		final_color = 0;
	float3		new_color = 0;
	float		seed = params->seed;

#ifdef RENDER_PATHTRACE
	float3		prev_color = img_data_float[g_id];
	new_color = pathtrace(scene,
# ifdef RENDER_OBJECTS
			objects,
# endif // RENDER_OBJECTS
# ifdef RENDER_MESH
		meshes_info, polygons, vertices, v_normals,
# endif // RENDER_MESH
		params, ray, params->pathtrace_params.max_depth, &seed, /*(float2)(21.1f, 13.f)*/(float2)(img_point.x + 1, img_point.y + 1));
	final_color = mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num);
	img_data_float[g_id] = final_color;
#endif // RENDER_PATHTRACE

#ifdef RENDER_RAYTRACE
	final_color = raytrace(scene,
# ifdef RENDER_OBJECTS
		objects,
# endif
		lights,
# ifdef RENDER_MESH
		meshes_info, polygons, vertices, v_normals,
#  ifdef RENDER_MESH_VTEXTURES
		v_textures,
#  endif
# endif // RENDER_MESH
		params, texture_info, texture_list, ray);
#endif // RENDER_RAYTRACE
	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));

}
