
bool				in_shadow(
		__constant t_scene *scene,
		__constant t_object *objects,
		float3 point,
		float3 light_dir,
		float ray_max)
{
	int		found_object = NOT_SET;

	closest_intersection(scene, objects, point, light_dir, 0.01f, ray_max, &found_object, 0);
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

	for (int i = 0; i < scene->lights_nbr; i++)
	{
		t_color		light_color = lights[i].color;
		float		intensity = 0.0f;
		float		ray_max;

		if (lights[i].type == AMBIENT)
		{
			intensity += lights[i].intensity;
			result_light_color.value = mix_avg_color(result_light_color, change_color_intensity(light_color, intensity), i + 1);
			continue;
		}
		else if (lights[i].type == POINT)
		{
			light_dir = lights[i].pos - point;
			ray_max = 1;
		}
		else if (lights[i].type == DIRECTIONAL)
		{
			light_dir = lights[i].dir;
			ray_max = INFINITY;
		}
		if (in_shadow(scene, objects, point, light_dir, ray_max))
			continue;
		normal_dot_light = dot(normal, light_dir);
		if (normal_dot_light > 0)
		{
			intensity = lights[i].intensity * normal_dot_light / (length(normal) * length(light_dir));
		}
		result_light_color.value = mix_avg_color(result_light_color, change_color_intensity(light_color, intensity), i + 1);
	}
	return (result_light_color);
}
