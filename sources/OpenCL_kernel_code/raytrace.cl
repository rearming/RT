
float3		reflect(t_ray *ray, float3 hit_normal)
{
	return ray->dir - 2 * dot(ray->dir, hit_normal) * hit_normal;
}

float		saturate(float value)
{
	return clamp(value, 0.0f, 1.0f);
}

float3		shade(
		t_ray *out_ray,
		t_rayhit *ray_hit,
		__constant t_material *material
		)
{
	if (ray_hit->distance < INFINITY)
	{
		float3 specular = (float3)(0.6f, 0.6f, 0.6f);

		out_ray->origin = ray_hit->pos + ray_hit->normal + 0.001f;
		out_ray->dir = reflect(out_ray, ray_hit->normal);
		out_ray->energy *= specular;

		return /*saturate(dot(ray_hit->normal, (float3)(0, 4, 4)) * -1.0f) * 0.4f * */material->albedo;
//		return (float3)(0, 0, 0); /// пока (0, 0, 0) чтобы было бесцветное отражение
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

	for (int i = 0; i < 1; ++i)
	{
		closest_intersection(scene, objects, &ray, &best_hit, &closest_obj_index); /// Trace() == closest_intersection
		result_color +=
				ray.energy * shade(&ray, &best_hit, &objects[closest_obj_index].material)
				* compute_light(scene, lights, objects, &best_hit);
		if (!ray_has_energy(&ray))
		{
			break;
		}
	}
	return result_color;
}