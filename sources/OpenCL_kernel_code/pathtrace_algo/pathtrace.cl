
# define LAMBERT_ALPHA 1.f

float3		shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		__constant t_material *material,
		float *seed,
		float2 pixel)
{
	if (hit->distance < INFINITY)
	{
		float	specular_chance = material->specular;
		float	chance = rt_randf(seed, pixel);

		if (chance < specular_chance)
		{
			const float		phong_alpha = material->smoothness;
			if (chance >= material->transmittance)
			{
				const float	phong_math_coeff = (phong_alpha + 2) / (phong_alpha + 1);
				ray->origin = hit->pos + hit->normal * RT_EPSILON;
				if (material->smoothness < MAX_SMOOTHNESS)
				{
					ray->dir = rand_dir_on_hemisphere(reflect(ray->dir, hit->normal), seed, pixel, phong_alpha);
					ray->energy *= specular_chance * material->albedo * sdot(hit->normal, ray->dir, phong_math_coeff);
				}
				else
				{
					ray->dir = reflect(ray->dir, hit->normal);
					ray->energy *= specular_chance * material->albedo;
				}
			}
			else
			{
				ray->origin = hit->pos;
				if (material->refraction > 1) /// если полностью прозрачный объект, не меняем направление луча
				{
					float3	refract_dir = refract(ray->dir, hit->normal, material->refraction);
					if (fast_length(refract_dir) > 0)
					/// фикс черного ореола над линзой, надо проверить как будет выглядеть со скайбоксом, если нормально, то убрать if
						ray->dir = rand_dir_on_hemisphere(refract(ray->dir, hit->normal, material->refraction), seed, pixel, phong_alpha);
				}
				ray->energy *= specular_chance * material->albedo;
				//todo sphere sampling refraction?
			}
		}
		else
		{
			ray->origin = hit->pos + hit->normal * RT_EPSILON;
			ray->dir = rand_dir_on_hemisphere(hit->normal, seed, pixel, LAMBERT_ALPHA);
			ray->energy *= (1 - specular_chance) * material->albedo;
		}
		return material->emission_color * material->emission_power;
	}
	else
	{
		ray->energy = 0;
		return get_float3_color(COL_BLACK);
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
	t_rayhit	hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
	int			closest_obj_index = NOT_SET;

	for (int i = 0; i < params->pathtrace_params.max_depth; ++i)
	{
		hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, &ray, &hit, &closest_obj_index);
		result_color += ray.energy;
		float3 shade_color = shade_pathtrace(&ray, &hit, &objects[closest_obj_index].material, seed, pixel);
		/// можно раскомментить, чтобы цвета светящихся объектов где emisson_power больше 1 были не белыми
//		if (i == 0 && round(fast_length(shade_color)) != 0)
//			shade_color /= objects[closest_obj_index].material.emission_power;
		result_color *= shade_color;
		if (!ray_has_energy(&ray))
			break;
	}
	return result_color;
}