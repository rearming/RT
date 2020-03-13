#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"

#include "math_utils.cl"
#include "utils.cl"

__kernel void	kernel_generate_primary_rays(
		__global const t_camera *camera,
		__global t_ray *out_rays_buffer,
		__global int *out_pixel_indices,
		__global int *num_pixel_rays_buffer)
{
	int		g_id = get_global_id(0);
	int3	img_point = get_img_point(g_id);

	num_pixel_rays_buffer[g_id] = 1;
	out_rays_buffer[g_id] = get_ray(convert_float3(img_point), camera);
	out_pixel_indices[g_id] = g_id;
}
