
void		calc_refraction_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		float3 color,
		float *seed,
		float2 pixel,
		float chance)
{
	const float		phong_alpha = material->smoothness;
	const float		phong_math_coeff = (phong_alpha + 2) / (phong_alpha + 1);
	const float3	refract_dir = convex_refract(ray->dir, hit->normal, material->refraction);

	ray->origin = hit->pos;
	if (material->smoothness < MAX_SMOOTHNESS)
		ray->dir = rand_dir_on_hemisphere(refract_dir, seed, pixel, phong_alpha);
	else
		ray->dir = refract_dir;
	ray->energy *= (1.f / chance) * color;
}

void		calc_reflection_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		float3 color,
		float *seed,
		float2 pixel,
		float chance)
{
	const float		phong_alpha = material->smoothness;
	const float		phong_math_coeff = (phong_alpha + 2) / (phong_alpha + 1);
	const float3	reflect_dir = reflect(ray->dir, hit->normal);

	ray->origin = hit->pos + hit->normal * RT_EPSILON;
	if (material->smoothness < MAX_SMOOTHNESS)
	{
		ray->dir = rand_dir_on_hemisphere(reflect_dir, seed, pixel, phong_alpha);
		ray->energy *= (1.f / chance) * color * sdot(hit->normal, ray->dir, phong_math_coeff);
	}
	else
	{
		ray->dir = reflect_dir;
		ray->energy *= (1.f / chance) * color;
	}
}

float3		shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material material,
		float *seed,
		float2 pixel)
{
	float	specular_chance = color_energy(material.specular);
	float	diffuse_chance = color_energy(material.diffuse);
	float	sum = specular_chance + diffuse_chance;
	specular_chance /= sum;
	diffuse_chance /= sum;

	float	chance = rt_randf(seed, pixel);

	if (material.emission_power > 0)
	{
		ray->energy = 0;
		return material.emission_color * material.emission_power;
	}
	if (chance < specular_chance)
	{
		chance = rt_randf(seed, pixel);
		if (chance < material.transmittance) // if transparent
		{
			calc_refraction_pathtrace(ray, hit, &material, material.specular, seed, pixel, specular_chance);
		}
		else
		{
			calc_reflection_pathtrace(ray, hit, &material, material.specular, seed, pixel, specular_chance);
		}
	}
	else //diffuse surface
	{
		chance = rt_randf(seed, pixel);
		if (chance < material.transmittance) // if transparent
		{
			calc_refraction_pathtrace(ray, hit, &material, material.diffuse, seed, pixel, diffuse_chance);
		}
		else
		{
			ray->origin = hit->pos + hit->normal * RT_EPSILON;
			ray->dir = rand_dir_on_hemisphere(hit->normal, seed, pixel, LAMBERT_ALPHA);
			ray->energy *= (1.f / diffuse_chance) * material.diffuse;
		}
	}
	return 0;
}
