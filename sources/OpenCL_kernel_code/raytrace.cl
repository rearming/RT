
float3		reflect(t_ray *ray, float3 hit_normal)
{
	return 2 * hit_normal * dot(hit_normal, ray->dir * -1) + ray->dir;

//	if (dot(ray->dir, hit_normal) < 0)
//		return ray->dir - 2 * dot(ray->dir, hit_normal) * hit_normal;
}

float		saturate(float value)
{
	return clamp(value, 0.0f, 1.0f);
}

float3		shade(
		t_ray *out_ray,
		t_rayhit *hit,
		__constant t_material *material
		)
{
	if (hit->distance < INFINITY)
	{
		float3 specular = (float3)(0.6f, 0.6f, 0.6f);

		out_ray->origin = hit->pos + hit->normal * 0.001f;
		out_ray->dir = reflect(out_ray, hit->normal);
//		printf("reflect: %.2f %.2f %.2f\n", out_ray->dir.x, out_ray->dir.y, out_ray->dir.z);
		out_ray->energy *= specular;

//		return (float3)(0.8f, 0.8f, 0.8f);
		return /*saturate(dot(hit->normal, (float3)(0, 4, 4)) * -1.0f) * 0.4f * */material->albedo;
	}
	else
	{
		out_ray->energy = 0;
		return get_float3_color(COL_BG);
	}
}

bool		ray_has_energy(t_ray *ray)
{
	return ray->energy.x > 0 || ray->energy.y > 0 || ray->energy.z > 0;
}

float3		raytrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		t_ray ray)
{
	float3		result_color = (float3)(0);

	t_rayhit	best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
	int			closest_obj_index = NOT_SET;

	for (int i = 0; i < 2; ++i)
	{
		int temp_obj_i = NOT_SET;

		closest_intersection(scene, objects, &ray, &best_hit, &closest_obj_index); /// Trace() == closest_intersection
		if (closest_obj_index != NOT_SET)
			result_color += ray.energy
				* shade(&ray, &best_hit, &objects[closest_obj_index].material)
				* compute_light(scene, lights, objects, &best_hit);
		else
		{
			result_color += ray.energy * get_float3_color(COL_BG);
			ray.energy = 0;
		}
		if (i == 0)
			temp_obj_i = closest_obj_index;
		else if (temp_obj_i == closest_obj_index) /// проверить шутку с эпсилоном и ray_min (что повторные лучи отражений не попадают в те же объекты)
			printf("wtf??\n");
		if (!ray_has_energy(&ray))
		{
			break;
		}
	}
	result_color /= 2;
	return result_color;
}