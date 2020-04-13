#ifndef RT_MATH_UTILS_H
# define RT_MATH_UTILS_H

# include "stdbool.h"
union cl_float3;

float		rt_minf(float a, float b);
float		rt_maxf(float a, float b);
float		rt_clampf(float value, float lower, float upper);
float		rt_saturatef(float value);
float		rt_lerpf(float a, float b, float t);

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

cl_float3	rt_float3_sub(cl_float3 a, cl_float3 b);
cl_float3	rt_float3_div(cl_float3 vec, cl_float scalar);
cl_float3	rt_float3_add(cl_float3 a, cl_float3 b);
cl_float	rt_vec_length(cl_float3 vec);
cl_float3	rt_vec_normalize(cl_float3 vec);

/*
**	float3 colors
*/
cl_float	float3_color_power(cl_float3 color);
cl_float3	get_float3_color(int hex_color);
int			get_int_color(cl_float3 float3_color);

/*
**	rotation
*/

void		rt_rotate_point(cl_float3 *point, cl_float3 angle);

#endif
