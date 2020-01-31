
float3			canvas_to_viewport(__global const t_camera *camera, float3 canvas_point)
{
	return (float3)
	(
		canvas_point.x * camera->viewport_width / WIN_WIDTH,
		canvas_point.y * camera->viewport_height / WIN_HEIGHT,
		camera->viewport_distance
	);
}

float3		reflect(float3 ray_dir, float3 normal)
{
	return ray_dir - 2 * dot(normal, ray_dir) * normal;
}

float3		convex_refract(float3 ray_dir, float3 normal, float refract_index)
{
	refract_index = 2.0f - refract_index;
	float normal_dot_ray = dot(normal, ray_dir);
	float3 refracted = (ray_dir * refract_index - normal * (-normal_dot_ray + refract_index * normal_dot_ray));
	return refracted;
}

float3		concave_refract(float3 ray_dir, float3 normal, float refract_index)
{
	float	normal_dot_ray = dot(normal, ray_dir);

	float k = 1.0 - refract_index * refract_index * (1.0 - normal_dot_ray * normal_dot_ray);
	if (k < 0.0)
		return (float3)(0);
	else
		return refract_index * ray_dir - (refract_index * normal_dot_ray + sqrt(k)) * normal;
}

bool		isset(int value)
{
	return (value != NOT_SET);
}

float		saturate(float value)
{
	return clamp(value, 0.0f, 1.0f);
}

float3		saturate_float3(float3 value)
{
	return clamp(value, 0.0f, 1.0f);
}

bool		ray_has_energy(t_ray *ray)
{
	return ray->energy.x > 0 || ray->energy.y > 0 || ray->energy.z > 0;
}
