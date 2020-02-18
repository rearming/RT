
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

/// возвращает вектор длинной вектор 1 умноженный
/// на cos угла между векторами
/// и перпендекулярный вектору 2 в плоскости векторов 1 и 2

float3	gram_schmidt_proc_r2(float3 vector_orto, float3 vector_basic)
{
	return (vector_orto - vector_basic * dot(vector_orto, vector_basic)
							/ dot(vector_basic, vector_basic));
}


/// поворачивает вектор 1 относительно оси,
/// заданной другим вектором на угол заданный в раданах
/// возвращает повернутый вектор 1

float3		vec_axis_rotate(float3 vec, float3 axis, float angle)
{
	float cos_ang, one_minus_cos, sin_ang;
	float3 rotate_vector;

	cos_ang = cos(angle);
	one_minus_cos = 1 - cos_ang;
	sin_ang = sin(angle);
	rotate_vector[0] = vec[0] * (cos_ang + one_minus_cos * axis[0] * axis[0])
			+ vec[1] * (one_minus_cos * axis[0] * axis[1] - sin_ang * axis[2])
			+ vec[2] * (one_minus_cos * axis[0] * axis[2] + sin_ang * axis[1]);
	rotate_vector[1] = vec[0] * (one_minus_cos * axis[0] * axis[1] + sin_ang * axis[2])
			+ vec[1] * (cos_ang + one_minus_cos * axis[1] * axis[1])
			+ vec[2] * (one_minus_cos * axis[1] * axis[2] - sin_ang * axis[0]);
	rotate_vector[2] = vec[0] * (one_minus_cos * axis[0] * axis[2] - sin_ang * axis[1])
			+ vec[1] * (one_minus_cos * axis[1] * axis[2] + sin_ang * axis[0])
			+ vec[2] * (cos_ang + one_minus_cos * axis[2] * axis[2]);
	return (rotate_vector);
}

float3		float3_float_mult(float3 vec, float num)
{
	float3 vec_out;
	vec_out[0] = vec[0] * num;
	vec_out[1] = vec[1] * num;
	vec_out[2] = vec[2] * num;
	return vec_out;
}