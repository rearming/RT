
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

t_color		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		float3 ray_dir,
		float3 origin,
		float3 normal,
		int depth,
		uint random_num)
{
	t_color		result_color = { COL_BG };
	t_color		indirect_light_color = { NOT_SET };
	t_color		direct_light_color = { NOT_SET };

	if (depth > params->pathtrace_params.max_depth)
		return result_color;

	int		closest_obj_index = NOT_SET;
	float	closest_intersect = closest_intersection(scene, objects, origin, ray_dir, 0.01f, INFINITY, &closest_obj_index, &result_color);

	if (closest_obj_index == NOT_SET)
		return result_color;

	float3 intersect_point = origin + (ray_dir * closest_intersect);
	normal = compute_normal(intersect_point, &objects[closest_obj_index]);

	direct_light_color = compute_lighting(scene, lights, objects, ray_dir, intersect_point, normal);

	uint rand_seed1 = rt_rand(random_num);
	uint rand_seed2 = rt_rand(rand_seed1);

	float3	new_ray_dir = rand_dir_on_hemisphere(normal, rand_distribution(rand_seed1), rand_distribution(rand_seed2));

	float	pdf = 1 / (2 * M_PI);
	indirect_light_color.value = COL_WHITE;

	result_color = change_color_intensity_colors(result_color, direct_light_color);

	// сделать функцию серии трансформаций через change_color_intensity
	// (мы не можем делать умножение так же. как в примерах из-за union)

//	result_color = change_color_intensity(result_color, objects[closest_obj_index].material.albedo);

//	result_color = change_color_intensity_colors(result_color, indirect_light_color);

//	result_color = objects[closest_obj_index].material.color;
//	float3 new_ray_dir =
//	indirect_light_color = pathtrace(scene, objects, lights, params, );
//	int	closest_obj_index = NOT_SET;

	return result_color;
}