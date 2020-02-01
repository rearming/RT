
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

# ifdef RAYTRACE
#  include "raytrace.cl"
#  include "light_computing.cl"
# endif

# ifdef PATHTRACE
#  include "pathtrace.cl"
#  include "shade_pathtrace.cl"
#  include "pathtrace_utils.cl"
# endif

# ifdef MESH_RENDER
#  include "mesh_render_utis.cl"
#  include "mesh_intersection.cl"
# endif

__kernel void	rt_main(
    __global const t_scene *scene,
    __global const t_object *objects,
    __global const t_light *lights,
    __global const t_opencl_params *params,
#ifdef MESH_RENDER
	__global const t_mesh_info *meshes_info,
    __global const t_polygon *polygons,
	__global const float3 *vertices,
	__global const float3 *v_normals,
#endif
#ifdef PATHTRACE
    __global float3 *img_data_float,
#endif
    __global int *img_data)
{
	int			g_id = get_global_id(0);
	int3		img_point = get_img_point(g_id);

	t_ray		ray = get_ray(convert_float3(img_point), &scene->camera);

	float3		final_color = 0;
	float3		new_color = 0;
	float		seed = params->seed;

#ifdef PATHTRACE
	float3		prev_color = img_data_float[g_id];
	new_color = pathtrace(scene, objects, lights, meshes_info, polygons, vertices, v_normals,
		params, ray, params->pathtrace_params.max_depth, &seed, (float2)(convert_float2(img_point).xy + 1));
	final_color = mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num);
	img_data_float[g_id] = final_color;
#endif

#ifdef RAYTRACE
//	final_color = raytrace(scene, objects, lights, meshes_info, polygons, vertices, v_normals, params, ray);
#endif
	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));

}
