
float		sdot(float3 a, float3 b, float coeff)
{
	return saturate(dot(a, b) * coeff);
}

float3		shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		float *seed,
		float2 pixel)
{
	if (hit->distance < INFINITY)
	{
		ray->origin = hit->pos + hit->normal * RT_EPSILON;
		ray->dir = rand_dir_on_hemishpere(hit->normal, seed, pixel);
		ray->energy *= 2 * material->albedo * sdot(hit->normal, ray->dir, 1);
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

	for (int i = 0; i < params->pathtrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		/// Trace() == closest_intersection
		closest_intersection(scene, objects, &ray, &best_hit, &closest_obj_index);
		if (closest_obj_index != NOT_SET)
			result_color += ray.energy
				* shade(&ray, &best_hit, &objects[closest_obj_index].material);
//		printf("hit.normal: x: %.2f y: %.2f z: %.2f\n", best_hit.normal.x, best_hit.normal.y, best_hit.normal.z);
		printf("rand: [%.3f]\n", rt_randf(&seed, pixel));
//		printf("ray->dir: x: %.2f y: %.2f z: %.2f\n", ray.dir.x, ray.dir.y, ray.dir.z);
		if (!ray_has_energy(&ray))
			break;
	}
	result_color /= 2;
	return result_color;
}