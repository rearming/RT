
bool				in_shadow(
		__constant t_scene *scene,
		__constant t_object *objects,
		t_ray *ray)
{
	int			found_object = NOT_SET;
	t_rayhit	dummy_hit = {(float3)(0), INFINITY, float3(0)};

	closest_intersection(scene, objects, ray, &dummy_hit, &found_object);
	return found_object != NOT_SET;
}

t_color				compute_lighting(
	__constant t_scene *scene,
	__constant t_light *lights,
	__constant t_object *objects,
	float3 ray_dir,
	float3 point,
	float3 normal)
{
	float3		light_dir;
	float		normal_dot_light;
	t_color		result_light_color;
	float		total_intensity = 0.0f;

	for (int i = 0; i < scene->lights_nbr; ++i)
	{
		float3		light_color = lights[i].color;
		float		intensity = 0.0f;

		if (lights[i].type == AMBIENT)
		{
			intensity = lights[i].intensity;
			total_intensity += intensity;
//			result_light_color.value = mix_avg_colors(result_light_color, change_color_intensity(light_color, intensity), i + 1);
			continue; /// тут CONTINUE, если AMBIENT !
		}
		else if (lights[i].type == POINT)
		{
			light_dir = lights[i].pos - point;
		}
		else if (lights[i].type == DIRECTIONAL)
		{
			light_dir = lights[i].dir;
		}
		if (in_shadow(scene, objects, &((t_ray){point, light_dir})))
			continue;
		normal_dot_light = dot(normal, light_dir);
		if (normal_dot_light > 0)
		{
			intensity = lights[i].intensity * normal_dot_light / (length(normal) * length(light_dir));
//			result_light_color.value = mix_avg_colors(result_light_color, change_color_intensity(light_color, intensity), i + 1);
			total_intensity += intensity;
		}
	}
	return result_light_color;
}
