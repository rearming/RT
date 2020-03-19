
#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
#include "prototypes.cl"

#include "color_utils.cl"
#include "utils.cl"
#include "math_utils.cl"
#include "gaussian_blur.cl"

__kernel void	kernel_depth_of_field(
		__global const t_camera *camera,
		__global const int *img_data,
		__global const float *depth_buffer,
		__global int *out_img_data)
{
	int		g_id = get_global_id(0);
	int2	img_point = get_img_point(g_id).xy;

	float	depth = clamp(depth_buffer[g_id], 0.0f, MAX_FOCAL_DISTANCE);
	int		blur_coeff;

	if (depth < camera->focal_distance - camera->aperture)
		blur_coeff = (int)round((camera->focal_distance - camera->aperture + 1 - depth) * camera->blur_strength);
	else if (depth > camera->focal_distance + camera->aperture)
		blur_coeff = (int)round((depth - (camera->focal_distance + camera->aperture - 1)) * camera->blur_strength);
	else
		blur_coeff = 1;

	float3	result_color = gauss_process_pixel(img_data, img_point.xy, blur_coeff);
	out_img_data[g_id] = get_int_color(result_color);
}
