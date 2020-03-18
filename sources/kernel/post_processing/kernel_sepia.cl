
#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
#include "prototypes.cl"

#include "color_utils.cl"
#include "utils.cl"

__kernel void	kernel_sepia(
		__global const int *img_data,
		__global int *out_img_data)
{
	int		g_id = get_global_id(0);
	float3	in_color = get_float3_color(img_data[g_id]);
	float3	out_color;

	out_color.x = (in_color.x * .393) + (in_color.y *.769) + (in_color.z * .189);
	out_color.y = (in_color.x * .349) + (in_color.y *.686) + (in_color.z * .168);
	out_color.z = (in_color.x * .272) + (in_color.y *.534) + (in_color.z * .131);

	out_img_data[g_id] = get_int_color(saturate_float3(out_color));
}

