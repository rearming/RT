
#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
#include "prototypes.cl"
#include "color_utils.cl"

__kernel void	kernel_gaussian_blur(
		__global const int *img_data,
		__global int *out_img_data)
{
	int		g_id = get_global_id(0);

	out_img_data[g_id] = get_int_color((get_float3_color(img_data[g_id])));
}
