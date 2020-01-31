
# define LAMBERT_ALPHA 1.f

float3		shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		__global const t_material *material,
		float *seed,
		float2 pixel)
{
	if (hit->distance < INFINITY)
	{
		float	specular_chance = color_energy(material->specular);
		float	chance = rt_randf(seed, pixel);

		if (material->emission_power > 0)
		{
			ray->energy = 0;
			return material->emission_color * material->emission_power;
		}
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
					{
						if (material->smoothness < MAX_SMOOTHNESS)
							ray->dir = rand_dir_on_hemisphere(refract(ray->dir, hit->normal, material->refraction), seed, pixel, phong_alpha);
						else
							ray->dir = refract(ray->dir, hit->normal, material->refraction);
					}
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
	}
	else
	{
		ray->energy = 0;
		return get_float3_color(COL_BLACK);
	}
	return 0;
}
