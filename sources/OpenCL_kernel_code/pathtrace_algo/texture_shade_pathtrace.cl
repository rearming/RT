
/*t_object *object*/
/*texture info bla bla*/

float3		texture_shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material material,
		float *seed,
		float2 pixel)
{
	if (hit->distance < INFINITY)
	{
		float	specular_chance = material.specular_texture;
		float	chance = rt_randf(seed, pixel);
//		float3	color = texture(); change material.emission_color to color

		if (material.emission_power > 0)
		{
			ray->energy = 0;
			return material.emission_color * material.emission_power;
		}
		if (chance < specular_chance)
		{
			chance = rt_randf(seed, pixel);
			const float		phong_alpha = material.smoothness;
			if (chance >= material.transmittance)
			{
				const float	phong_math_coeff = (phong_alpha + 2) / (phong_alpha + 1);
				ray->origin = hit->pos + hit->normal * RT_EPSILON;
				if (material.smoothness < MAX_SMOOTHNESS)
				{
					ray->dir = rand_dir_on_hemisphere(reflect(ray->dir, hit->normal), seed, pixel, phong_alpha);
					ray->energy *= (1.f / specular_chance) * material.specular * sdot(hit->normal, ray->dir, phong_math_coeff);
				}
				else
				{
					ray->dir = reflect(ray->dir, hit->normal);
					ray->energy *= (1.f / specular_chance) * material.specular;
				}
			}
			else
			{
				ray->origin = hit->pos;
				float3	refract_dir = convex_refract(ray->dir, hit->normal, material.refraction);
				if (material.smoothness < MAX_SMOOTHNESS)
					ray->dir = rand_dir_on_hemisphere(refract_dir, seed, pixel, phong_alpha);
				else
					ray->dir = refract_dir;
				ray->energy *= (1.f / specular_chance) * material.specular;
			}
		}
		else
		{
			ray->origin = hit->pos + hit->normal * RT_EPSILON;
			ray->dir = rand_dir_on_hemisphere(hit->normal, seed, pixel, LAMBERT_ALPHA);
			ray->energy *= (1.f / (1 - specular_chance)) * material.diffuse;
		}
	}
	else
	{
		ray->energy = 0;
		return get_float3_color(COL_BLACK); //add skubox
	}
	return 0;
}
