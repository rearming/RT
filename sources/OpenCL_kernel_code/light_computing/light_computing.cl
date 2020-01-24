
bool				in_shadow(
		__constant t_scene *scene,
		__constant t_object *objects,
		t_ray ray,
		t_light_type light_type)
{
	int			found_object = NOT_SET;
	t_rayhit	out_hit = {(float3)(0), INFINITY, (float3)(0)};

	closest_intersection(scene, objects, &ray, &out_hit, &found_object);
	if (light_type == POINT && out_hit.distance > 1) /// проверяем луч только до источника света
		return false;
	return found_object != NOT_SET && objects[found_object].material.transmittance <= 0;
}

float				compute_light(
	__constant t_scene *scene,
	__constant t_light *lights,
	__constant t_object *objects,
	t_rayhit *hit)
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
		if (in_shadow(scene, objects, (t_ray){hit->pos, light_dir}, lights[i].type))
			continue;
		float	normal_dot_light = dot(hit->normal, light_dir);
		if (normal_dot_light > 0)
		{
			intensity += lights[i].intensity * normal_dot_light / (length(hit->normal) * length(light_dir));
		}
	}
	return intensity;
}
