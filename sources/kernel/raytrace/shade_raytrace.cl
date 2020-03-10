
//__global const t_texture_info *texture_info,
//__global const float *texture_list,
//__global const t_object *object

float3		shade_raytrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material
		)
{
	float3	diffuse_color = material->diffuse;

	if (material->transmittance <= 0.0f) // if not transmit
	{
//#ifdef RENDER_TEXTURES
//		if (material->texture_number != NOT_SET)
//			diffuse_color = texture(ray, hit, &texture_info[material->texture_number], texture_list, object);
//#endif
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
//#ifdef RENDER_TEXTURES
//	if (material->texture_number != NOT_SET)
//		return diffuse_color;
//#endif
	return material->emission_power > 0.0f ? material->emission_color : diffuse_color;
}
