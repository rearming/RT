#include "rt.h"
#include "rt_math_utils.h"

cl_float3	rt_float3_sub(cl_float3 a, cl_float3 b)
{
	return ((cl_float3){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z});
}

cl_float3	rt_float3_add(cl_float3 a, cl_float3 b)
{
	return ((cl_float3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z});
}

cl_float3	rt_float3_div(cl_float3 vec, cl_float scalar)
{
	return ((cl_float3){.x = vec.x / scalar, .y = vec.y / scalar, .z = vec.z / scalar});
}

cl_float	rt_vec_length(cl_float3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

cl_float3	rt_vec_normalize(cl_float3 vec)
{
	const cl_float	length = rt_vec_length(vec);
	return (length == 0 || length == 1 ? vec : (cl_float3){.x = vec.x / length,
														.y = vec.y / length,
														.z = vec.z / length});
}
