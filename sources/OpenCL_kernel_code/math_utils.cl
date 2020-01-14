
void		rotate_y(float3 *point, float angle)
{
	float3		temp;

	temp = *point;
	point->x = point->x * cos(angle) + point->z * sin(angle);
	point->z = -temp.x * sin(angle) + point->z * cos(angle);
}

void		rotate_x(float3 *point, float angle)
{
	float3		temp;

	temp = *point;
	point->y = point->y * cos(angle) + point->z * sin(angle);
	point->z = -temp.y * sin(angle) + point->z * cos(angle);
}

void		rotate_z(float3 *point, float angle)
{
	float3		temp;

	temp = *point;
	point->x = point->x * cos(angle) - point->y * sin(angle);
	point->y = temp.x * sin(angle) + point->y * cos(angle);
}

float3		degree_to_rad(float3 rotation_degrees)
{
	float3	radians;

	radians.x = rotation_degrees.x * M_PI_180;
	radians.y = rotation_degrees.y * M_PI_180;
	radians.z = rotation_degrees.z * M_PI_180;
	return (radians);
}

void		rotate_point(float3 *point, float3 angle)
{
	angle = degree_to_rad(angle);
	rotate_x(point, angle.x);
	rotate_y(point, angle.y);
	rotate_z(point, angle.z);
}
