/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	map_value(float value, float min, float max, float new_min, float new_max)
{
	return (value - min) / (max - min) * (new_max - new_min) + new_min;
}

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
	rotate_vector.x = vec.x * (cos_ang + one_minus_cos * axis.x * axis.x)
			+ vec.y * (one_minus_cos * axis.x * axis.y - sin_ang * axis.z)
			+ vec.z * (one_minus_cos * axis.x * axis.z + sin_ang * axis.y);
	rotate_vector.y = vec.x * (one_minus_cos * axis.x * axis.y + sin_ang * axis.z)
			+ vec.y * (cos_ang + one_minus_cos * axis.y * axis.y)
			+ vec.z * (one_minus_cos * axis.y * axis.z - sin_ang * axis.x);
	rotate_vector.z = vec.x * (one_minus_cos * axis.x * axis.z - sin_ang * axis.y)
			+ vec.y * (one_minus_cos * axis.y * axis.z + sin_ang * axis.x)
			+ vec.z * (cos_ang + one_minus_cos * axis.z * axis.z);
	return (rotate_vector);
}
