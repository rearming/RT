#include "rt.h"
#include "rt_math_utils.h"

bool		rt_float3_equals(cl_float3 a, cl_float3 b)
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

cl_float3	saturate_float3(cl_float3 value)
{
	return ((cl_float3){{
		ft_saturate(value.x),
		ft_saturate(value.y),
		ft_saturate(value.z)}});
}
