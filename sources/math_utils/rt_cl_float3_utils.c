#include "rt.h"

t_bool		rt_clfloat3_equals(cl_float3 a, cl_float3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
