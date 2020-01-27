
float3		shade(
		t_ray *ray,
		t_rayhit *hit,
		__constant t_material *material)
{
	if (hit->distance < INFINITY)
	{
		///умножение на epsilon нужно для того чтобы на маленьких расстояниях объекты не пропускались

		if (material->transmittance > 0)
		{
			ray->origin = hit->pos;
			if (material->refraction > 1)
				ray->dir = refract(ray->dir, hit->normal, material->refraction);
		}
		else
		{
			ray->origin = hit->pos + hit->normal * RT_EPSILON;
			ray->dir = reflect(ray->dir, hit->normal);
			ray->energy *= material->albedo * material->specular;
		}
		return material->albedo;
	}
	else
	{
		ray->energy = 0;
		return get_float3_color(COL_BG);
	}
}

float3		raytrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		t_ray ray)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit;
	int			closest_obj_index = NOT_SET;

	for (int i = 0; i < params->raytrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, &ray, &best_hit, &closest_obj_index);
		if (closest_obj_index != NOT_SET)
		{
			float light_i = 0;
			if (objects[closest_obj_index].material.transmittance <= 0)
				light_i = compute_light(scene, lights, objects, &best_hit);
			result_color += ray.energy
					* light_i
					* shade(&ray, &best_hit, &objects[closest_obj_index].material);
		}
		else
		{
			ray.energy = 0;
			result_color = get_float3_color(COL_BG);
		}
		if (!ray_has_energy(&ray))
			break;
	}

	result_color = saturate_float3(result_color);
//	result_color = result_color / (result_color + (float3)(1.f));
	return result_color;
}