#include "rt.h"
#include "rt_math_utils.h"

cl_float3	vec_subtract(cl_float3 a, cl_float3 b)
{
	return ((cl_float3){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z});
}

cl_float3	vec_divide(cl_float3 vec, cl_float scalar)
{
	return ((cl_float3){.x = vec.x / scalar, .y = vec.y / scalar, .z = vec.z / scalar});
}

cl_float	vec_length(cl_float3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

cl_float3	vec_normalize(cl_float3 vec)
{
	const cl_float	length = vec_length(vec);
	return (length == 0 || length == 1 ? vec : (cl_float3){.x = vec.x / length,
														.y = vec.y / length,
														.z = vec.z / length});
}
