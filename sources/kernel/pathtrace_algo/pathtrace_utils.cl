void		create_coordinate_system(float3 normal, float3 *normal_x, float3 *normal_z)
{
	*normal_x = fabs(normal.x) > fabs(normal.y)
				? fast_normalize((float3)(normal.z, 0.0f, -normal.x))
				: fast_normalize((float3)(0.0f, -normal.z, normal.y));
	*normal_z = cross(normal, *normal_x);
}

float3		sample_hemisphere(float *seed, float2 pixel_seed, float phong_alpha)
{
	float	cos_theta = pow(rt_randf(seed, pixel_seed), 1.0f / (phong_alpha + 1.0f));
	float	sin_theta = sqrt(1.0f - cos_theta * cos_theta);
	float	phi = 2.0f * M_PI * rt_randf(seed, pixel_seed);

	float3	sample = (float3)(cos(phi) * sin_theta, sin(phi) * sin_theta, cos_theta);
	return sample.xzy; /// у в координатной системе вверх направлена ось Y, а не Z
	/// может потом просто поменять порядок в float3 sample = [...]
}

float3		rand_dir_on_hemisphere(
		float3 normal,
		float *seed,
		float2 pixel_seed,
		float phong_alpha)
{
	float3 normal_x, normal_z;

	create_coordinate_system(normal, &normal_x, &normal_z);
	float3 sample = sample_hemisphere(seed, pixel_seed, phong_alpha);
	float3 sample_world_space = (float3) // может быть normal_z и normal_x поменять местами
	(
		sample.x * normal_z.x + sample.y * normal.x + sample.z * normal_x.x,
		sample.x * normal_z.y + sample.y * normal.y + sample.z * normal_x.y,
		sample.x * normal_z.z + sample.y * normal.z + sample.z * normal_x.z
	);
	return sample_world_space;
}

bool	russian_roulette_terminate(t_ray *ray, float *seed, float2 pixel_seed)
{
	float p = color_energy(ray->energy);
	if (saturate(rt_randf(seed, pixel_seed)) > p)
		return true;
	ray->energy *= (1.0f / p);
	return false;
}
