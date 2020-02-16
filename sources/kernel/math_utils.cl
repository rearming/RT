
float		sdot(float3 a, float3 b, float coeff)
{
	return saturate(dot(a, b) * coeff);
}

int 				in_range_inclusive(float number, float min, float max)
{
	return number >= min && number <= max ? true : false;
}

uint		rt_rand(uint seed)
{
	seed = (seed ^ 61) ^ (seed >> 16);
	seed *= 9;
	seed = seed ^ (seed >> 4);
	seed *= 0x27d4eb2d;
	seed = seed ^ (seed >> 15);
	return seed;
}

float		rt_fract(float x)
{
	return min(x - floor(x), 0x1.fffffep-1f);
}

float		rt_randf(float *seed, float2 pixel)
{
	float result = rt_fract(sin(*seed / 100.0f * dot(pixel, (float2)(12.9898f, 78.233f))) * 43758.5453f);
	*seed += 1.0f;
	return result;
}

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

void		rotate_point(float3 *point, float3 angle)
{
	angle = degree_to_rad(angle);
	rotate_x(point, angle.x);
	rotate_y(point, angle.y);
	rotate_z(point, angle.z);
}

float3		degree_to_rad(float3 rotation_degrees)
{
	float3	radians;

	radians.x = rotation_degrees.x * M_PI_180;
	radians.y = rotation_degrees.y * M_PI_180;
	radians.z = rotation_degrees.z * M_PI_180;
	return (radians);
}
