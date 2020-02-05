#ifndef RT_MATH_UTILS_H
# define RT_MATH_UTILS_H

# include "stdbool.h"
union cl_float3;

float		ft_minf(float a, float b);
float		ft_maxf(float a, float b);
float		ft_clampf(float value, float lower, float upper);
float		ft_saturate(float value);

/*
** float3
*/
cl_float3	rt_degree_to_rad(cl_float3 rotation_degrees);
bool		rt_float3_equals(cl_float3 a, cl_float3 b);
cl_float3	mul_float3(cl_float3 vec, float mul);
cl_float3	saturate_float3(cl_float3 value);

/*
**	float3 colors
*/
cl_float	float3_color_power(cl_float3 color);
cl_float3	get_float3_color(int hex_color);

#endif