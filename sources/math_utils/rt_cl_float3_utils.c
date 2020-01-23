#include "rt.h"

t_bool		rt_float3_equals(cl_float3 a, cl_float3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

cl_float3	mul_float3(cl_float3 vec, float mul)
{
	cl_float3	result;

	result.x = vec.x * mul;
	result.y = vec.y * mul;
	result.z = vec.z * mul;
	return (result);
}