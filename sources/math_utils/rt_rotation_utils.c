#include "rt.h"

cl_float3	rt_degree_to_rad(cl_float3 rotation_degrees)
{
	cl_float3	radians;

	radians.x = rotation_degrees.x * M_PI_180;
	radians.y = rotation_degrees.y * M_PI_180;
	radians.z = rotation_degrees.z * M_PI_180;
	return (radians);
}

void		rotate_y(cl_float3 *point, float angle)
{
	cl_float3		temp;

	temp = *point;
	point->x = point->x * cosf(angle) + point->z * sinf(angle);
	point->z = -temp.x * sinf(angle) + point->z * cosf(angle);
}

void		rotate_x(cl_float3 *point, float angle)
{
	cl_float3		temp;

	temp = *point;
	point->y = point->y * cosf(angle) + point->z * sinf(angle);
	point->z = -temp.y * sinf(angle) + point->z * cosf(angle);
}

void		rotate_z(cl_float3 *point, float angle)
{
	cl_float3		temp;

	temp = *point;
	point->x = point->x * cosf(angle) - point->y * sinf(angle);
	point->y = temp.x * sinf(angle) + point->y * cosf(angle);
}

void		rt_rotate_point(cl_float3 *point, cl_float3 angle)
{
	rotate_x(point, angle.x);
	rotate_y(point, angle.y);
	rotate_z(point, angle.z);
}
