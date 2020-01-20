
float3			canvas_to_viewport(__constant t_camera *camera, float3 canvas_point)
{
	return (float3)
	(
		canvas_point.x * camera->viewport_width / WIN_WIDTH,
		canvas_point.y * camera->viewport_height / WIN_HEIGHT,
		camera->viewport_distance
	);
}

float3		reflect(float3 ray_dir, float3 hit_normal)
{
	return ray_dir - 2 * dot(hit_normal, ray_dir) * hit_normal;
}

float		saturate(float value)
{
	return clamp(value, 0.0f, 1.0f);
}

bool		ray_has_energy(t_ray *ray)
{
	return ray->energy.x > 0 || ray->energy.y > 0 || ray->energy.z > 0;
}
