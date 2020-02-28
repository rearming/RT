#include "rt.h"

float		rt_minf(float a, float b)
{
	return (a < b ? a : b);
}

float		rt_maxf(float a, float b)
{
	return (a < b ? b : a);
}

float		rt_clampf(float value, float lower, float upper)
{
	return rt_minf(upper, rt_maxf(lower, value));
}

float		rt_saturatef(float value)
{
	return (rt_clampf(value, 0.f, 1.f));
}

float		rt_lerpf(float a, float b, float t)
{
	return (a + (b - a) * t);
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