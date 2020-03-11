
float3		texture_shade_raytrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		__global const t_object *object)
{
	float3	diffuse_color = material->diffuse;

	diffuse_color = texture(ray, hit, &texture_info[material->texture_number], texture_list, object);
	if (material->transmittance <= 0.0f)
	{
		ray->origin = hit->pos + hit->normal * RT_EPSILON;
		ray->dir = reflect(ray->dir, hit->normal);
		ray->energy *= material->specular;
	}
	else
	{
		ray->origin = hit->pos;
		ray->dir = convex_refract(ray->dir, hit->normal, material->refraction);
		ray->energy *= material->specular;
	}
	return diffuse_color;
}
