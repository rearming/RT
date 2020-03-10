
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"
#include "color_utils.cl"

__kernel void	kernel_texture_fill_img_data(
		__global const int *texture_pixel_indices,

		__global const t_renderer_params *params,
		__global const float3 *temp_float3_img_data,
		__global const float3 *main_float3_img_data,
		__global int *img_data)
{
	int			g_id = get_global_id(0);
	int			pixel_index = texture_pixel_indices[g_id];
	float3		new_color = temp_float3_img_data[pixel_index];

	img_data[pixel_index] = get_int_color(correct_hdr(params->gamma, params->exposure, new_color));
}