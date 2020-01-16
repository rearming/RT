#include "rt.h"

cl_float3	rt_degree_to_rad(cl_float3 rotation_degrees)
{
	cl_float3	radians;

	radians.x = rotation_degrees.x * M_PI_180;
	radians.y = rotation_degrees.y * M_PI_180;
	radians.z = rotation_degrees.z * M_PI_180;
	return (radians);
}
