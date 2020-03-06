
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"
#include "color_utils.cl"

__kernel void	kernel_fill_img_data(
		__global __read_only const t_renderer_params *params,
		__global __read_only const float3 *temp_float3_img_data,
		__global float3 *main_float3_img_data,
		__global __write_only int *img_data)
{
	int			g_id = get_global_id(0);
	float3		prev_color = main_float3_img_data[g_id];
	float3		new_color = temp_float3_img_data[g_id];
	float3		final_color;

#ifdef RENDER_PATHTRACE
	final_color = mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num);
	main_float3_img_data[g_id] = final_color;
#endif
#ifdef RENDER_RAYTRACE
	final_color = new_color;
#endif
	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));
}
