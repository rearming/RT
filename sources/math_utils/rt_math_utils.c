#include "rt.h"

float		ft_minf(float a, float b)
{
	return (a < b ? a : b);
}

float		ft_maxf(float a, float b)
{
	return (a < b ? b : a);
}

float		ft_clampf(float value, float lower, float upper)
{
	return ft_minf(upper, ft_maxf(lower, value));
}

float		ft_saturate(float value)
{
	return (ft_clampf(value, 0.f, 1.f));
}

//float		length(cl_float3 v)
//{
//	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
//}
//
//cl_float3	normalize(cl_float3 v1)
//{
//	float		len;
//	cl_float3	v;
//
//	v = v1;
//	len = length(v);
//	if (len == 1 || len == 0)
//		return (v);
//	v.x /= len;
//	v.y /= len;
//	v.z /= len;
//	return (v);
//}