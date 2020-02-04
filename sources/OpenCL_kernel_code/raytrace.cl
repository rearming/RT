
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
		__constant t_material *material,
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		__constant t_object *object)
{
	if (hit->distance < INFINITY)
	{
		float3	diffuse_color = material->albedo;

		if (material->texture_number >= 0 && material->texture_number < TEXTURE_NUM)
			 diffuse_color = texture(out_ray, hit, &texture_info[material->texture_number], texture_list, object);

		out_ray->origin = hit->pos + hit->normal;
		out_ray->dir = reflect(out_ray, hit->normal);
		out_ray->energy *= material->specular;

		return diffuse_color;
	}
	else
	{
		out_ray->energy = 0;
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
		__global t_texture_info *texture_info,
		__global float *texture_list,
		t_ray ray,
		float3 img_point)
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
		{
			result_color += ray.energy * compute_light(scene, lights, objects, &best_hit)
					* shade(&ray, &best_hit, &objects[closes_index].material, &texture_info[0], texture_list, &objects[closes_index]);
		}
		else
		{
			normal = skybox_normal(ray);
			result_color += ray.energy * skybox_color(&texture_info[0], texture_list, &normal);
			ray.energy = (float3)(0, 0, 0);
		}
		if (!ray_has_energy(&ray))
			break;
	}
	result_color /= 2;
	return result_color;
}