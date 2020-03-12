
float3		shade_raytrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material
		)
{
	float3	diffuse_color = material->diffuse;

	if (material->transmittance <= 0.0f) // if not transmit
	{
		ray->origin = hit->pos + hit->normal * RT_EPSILON;
		ray->dir = reflect(ray->dir, hit->normal);
		ray->energy *= material->specular; // if material is diffuse -> material->specular == 0 -> energy = 0;
	}
	else
	{
		ray->origin = hit->pos;
		ray->dir = convex_refract(ray->dir, hit->normal, material->refraction);
		ray->energy *= material->specular;
	}
	return material->emission_power > 0.0f ? material->emission_color : diffuse_color;
}
