void		create_coordinate_system(float3 normal, float3 *normal_x, float3 *normal_z)
{
	*normal_x = fabs(normal.x) > fabs(normal.y)
				? fast_normalize((float3)(normal.z, 0, -normal.x))
				: fast_normalize((float3)(0, -normal.z, normal.y));
	*normal_z = cross(normal, *normal_x);
}

float3		uniform_sample_hemisphere(float rand1, float rand2)
{
	float sin_theta = sqrtf(1 - rand1 * rand1);
	float phi = 2 * M_PI * rand2;
	float x = sin_theta * cosf(phi);
	float z = sin_theta * sinf(phi);
	return (float3)(x, rand1, z); // rand1, 1, etc.. какой тут будет Y?
}

float3		rand_dir_on_hemisphere(
		float3 normal,
		float rand1,
		float rand2)
{
	float3 normal_x, normal_z;

	float3 sample = uniform_sample_hemisphere(rand1, rand2);
	float3 sample_world_space = (float3) // может быть normal_z и normal_x поменять местами
			(
					sample.x * normal_z.x + sample.y * normal.x + sample.z * normal_x.x,
					sample.x * normal_z.y + sample.y * normal.y + sample.z * normal_x.y,
					sample.x * normal_z.z + sample.y * normal.z + sample.z * normal_x.z
			);
	return sample_world_space;
}