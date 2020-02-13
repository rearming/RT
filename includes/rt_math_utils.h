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

cl_float3	fmin_float3(cl_float3 a, cl_float3 b);
cl_float3	fmax_float3(cl_float3 a, cl_float3 b);

cl_float2	fmin_float2(cl_float2 a, cl_float2 b);
cl_float2	fmax_float2(cl_float2 a, cl_float2 b);


cl_float3	vec_subtract(cl_float3 a, cl_float3 b);
cl_float3	vec_divide(cl_float3 vec, cl_float scalar);
cl_float	vec_length(cl_float3 vec);
cl_float3	vec_normalize(cl_float3 vec);

/*
**	float3 colors
*/
cl_float	float3_color_power(cl_float3 color);
cl_float3	get_float3_color(int hex_color);

/*
**	rotation
*/

void		rt_rotate_point(cl_float3 *point, cl_float3 angle);

#endif
