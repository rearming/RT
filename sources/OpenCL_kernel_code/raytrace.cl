
float3		reflect(t_ray *ray, float3 hit_normal)
{
	return ray->dir - 2 * dot(hit_normal, ray->dir) * hit_normal;
}

float		saturate(float value)
{
	return clamp(value, 0.0f, 1.0f);
}

float3		shade(
		t_ray *out_ray,
		t_rayhit *hit,
		t_texture_info texture_info,
		__constant float *texture_list,
		__constant t_material *material)
{
	if (hit->distance < INFINITY)
	{
		out_ray->origin = hit->pos + hit->normal;
		out_ray->dir = reflect(out_ray, hit->normal);
		out_ray->energy *= material->specular;

		return material->albedo;
	}
	else
	{
		out_ray->energy = 0;
		//float3 normal = skybox_normal(out_ray);				//count_normal
		//return get_float3_color(skybox_color(texture_list, texture_info, normal));
		return get_float3_color(COL_BG); //add here skybox
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
		__constant t_texture_info *texture_info,
		__constant float *texture_list,
		t_ray ray)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit;
	int			closes_index = NOT_SET;
	float3		normal = (float3)(0);

	for (int i = 0; i < 2; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, &ray, &best_hit, &closes_index); /// Trace() == closest_intersection
		if (closes_index != NOT_SET)
			result_color += ray.energy
				* compute_light(scene, lights, objects, &best_hit)
				* shade(&ray, &best_hit, texture_info[0], texture_list, &objects[closes_index].material);
		else
		{
			result_color += ray.energy * get_float3_color(COL_BG);

			//printf("here\n");
			normal = skybox_normal(ray);	//skybox_normal
			result_color =get_float3_color(skybox_color(texture_list, texture_info[0], normal));
			//printf("ray = %i %i %i normal = %i, %i, %i\n", ray.origin.x, ray.origin.y, ray.origin.z, normal.x, normal.y, normal.z);
			//result_color += ray.energy *
			//		get_float3_color(skybox_color(texture_list, texture_info[0], normal)); //add here skybox
			ray.energy = (float3)(0, 0, 0);
		}
		if (!ray_has_energy(&ray))
			break;
	}
	result_color /= 2;
	return result_color;
}