
#include "rt.h"

cl_float3		get_float3_color(int hex_color)
{
	const t_color		color = {hex_color};

	return ((cl_float3){{
		(float)color.rgb.r / 255,
		(float)color.rgb.g / 255,
		(float)color.rgb.b / 255}});
}
