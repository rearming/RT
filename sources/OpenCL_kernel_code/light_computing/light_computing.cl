
bool				in_shadow(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_light_type light_type)
{
	int			found_object = NOT_SET;
	int			found_polygon = NOT_SET;
	t_rayhit	out_hit = {(float3)(0), INFINITY, (float3)(0)};

	closest_intersection(scene, objects, polygons, vertices, v_normals, ray, &out_hit, &found_polygon, &found_object);
	if (light_type == POINT && out_hit.distance > 1) /// проверяем луч только до источника света
		return false;
	return (found_object != NOT_SET || found_polygon != NOT_SET) && objects[found_object].material.transmittance <= 0;
}

float				blinn_phong_shine(float3 ray_dir, float3 light_dir, float3 normal, float phong_exp)
{
	float3	half_dir = normalize(ray_dir + light_dir);
	float	specular_angle = max(dot(half_dir, normal), 0.0f);
	return pow(specular_angle, phong_exp);
}

float				compute_light(
	__global const t_scene *scene,
	__global const t_light *lights,
	__global const t_object *objects,
	__global const t_polygon *polygons,
	__global const float3 *vertices,
	__global const float3 *v_normals,
	t_rayhit *hit,
	t_ray *ray,
	t_material *hit_material)
{
	float		intensity = 0.0f;

	for (int i = 0; i < scene->lights_nbr; ++i)
	{
		float3		light_dir;

		if (lights[i].type == AMBIENT)
		{
			intensity = lights[i].intensity;
			continue;
		}
		else if (lights[i].type == POINT)
		{
			light_dir = lights[i].pos - hit->pos;
		}
		else if (lights[i].type == DIRECTIONAL)
		{
			light_dir = lights[i].dir;
		}
		t_ray	shadow_ray;
		shadow_ray.origin = hit->pos;
		shadow_ray.dir = light_dir;
		if (in_shadow(scene, objects, polygons, vertices, v_normals,
				&shadow_ray, lights[i].type))
			continue;
		float	normal_dot_light = dot(hit->normal, light_dir);
		if (normal_dot_light > 0)
		{
			intensity += lights[i].intensity * normal_dot_light / (length(hit->normal) * length(light_dir));
			if (hit_material->phong_exp > 1)
				intensity += intensity * blinn_phong_shine(ray->dir, light_dir, hit->normal, hit_material->phong_exp);
		}
	}
	return intensity;
}
