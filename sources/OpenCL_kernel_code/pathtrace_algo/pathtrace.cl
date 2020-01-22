
float		sdot(float3 a, float3 b, float coeff)
{
	return saturate(dot(a, b) * coeff);
}

float		color_energy(float3 color)
{
	return dot(color, 1.f / 3.f);
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
//		float3 new_albedo = ...
		float specular_chance = color_energy(material->specular);
		float diffuse_chance = color_energy(material->albedo);
		float sum = specular_chance + diffuse_chance;
		specular_chance /= sum;
		diffuse_chance /= sum;

		float	chance = rt_randf(seed, pixel);

		ray->origin = hit->pos + hit->normal * RT_EPSILON;

		if (chance < specular_chance)
		{
			ray->dir = reflect(ray->dir, hit->normal);
			ray->energy *= (1.f / specular_chance) * material->specular * dot(hit->normal, ray->dir);
		}
		else
		{
			ray->dir = rand_dir_on_hemisphere(hit->normal, seed, pixel);
			ray->energy *= (1.f / diffuse_chance) * 2 * material->albedo * dot(hit->normal, ray->dir);
		}
		/// (1.f / specular(diffuse)_chance) = PDF!
		// todo проверить dot() vs sdot()
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
		float *seed,
		float2 pixel)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
	int			closest_obj_index = NOT_SET;

	for (int i = 0; i < params->pathtrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, &ray, &best_hit, &closest_obj_index);
		result_color += ray.energy *
				shade_pathtrace(&ray, &best_hit, &objects[closest_obj_index].material, seed, pixel);
		if (!ray_has_energy(&ray))
			break;
	}
	return result_color;
}