
float		sdot(float3 a, float3 b, float coeff)
{
	return saturate(dot(a, b) * coeff);
}

float3		shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		__constant t_material *material,
		float *seed,
		float2 pixel)
{
	if (hit->distance < INFINITY)
	{
		ray->origin = hit->pos + hit->normal * RT_EPSILON;
		ray->dir = rand_dir_on_hemisphere(hit->normal, seed, pixel);
		ray->energy *= 2 * material->albedo * dot(hit->normal, ray->dir);
//		if ((int)pixel.x == 565 && (int)pixel.y == 942)
//		{
////			printf("new ray->dir: %f %f %f\n", ray->dir.x, ray->dir.y, ray->dir.z);
//			printf("dot: %.2f\n", dot(ray->dir, hit->normal));
//			printf("ray->energy: %f %f %f\n", ray->energy.x, ray->energy.y, ray->energy.z);
//		}

		return 0.0f;
	}
	else
	{
		ray->energy = 0;
		return get_float3_color(COL_WHITE);
	}
}

float3		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		t_ray ray,
		int depth,
		float seed,
		float2 pixel)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
	int			closest_obj_index = NOT_SET;

	int			temp_index = NOT_SET;

	for (int i = 0; i < params->pathtrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, &ray, &best_hit, &closest_obj_index);
//		if ((int)pixel.x == 565 && (int)pixel.y == 942)
//		{
//			printf("i: %d closest_obj_index: %d\n", i, closest_obj_index);
//		}
		float3 energy = ray.energy;
		result_color += energy * shade_pathtrace(&ray, &best_hit, &objects[closest_obj_index].material, &seed, pixel);

		temp_index = closest_obj_index;

		if (!ray_has_energy(&ray))
			break;
	}
//	if ((int)pixel.x == 565 && (int)pixel.y == 942)
//		printf("result_color: %f %f %f\n", result_color.x, result_color.y, result_color.z);
//	result_color = saturate_float3(result_color);
	return result_color;
}