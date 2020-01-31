
float3		shade(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material)
{
	if (hit->distance < INFINITY)
	{
		if (material->transmittance <= 0)
		{
			ray->origin = hit->pos + hit->normal * RT_EPSILON;
			ray->dir = reflect(ray->dir, hit->normal);
			ray->energy *= material->specular;
		}
		else
		{
			ray->origin = hit->pos;
			if (material->refraction > 1)
				ray->dir = refract(ray->dir, hit->normal, material->refraction);
			ray->energy *= material->specular;
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
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_light *lights,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		__global const t_opencl_params *params,
		t_ray ray)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit;
	int			closest_obj_index = NOT_SET;
	int			closest_polygon_index = NOT_SET;

	for (int i = 0; i < params->raytrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, polygons, vertices, v_normals, &ray, &best_hit, &closest_polygon_index, &closest_obj_index);
		float		light_intensity = 0;
		t_material	hit_material;
		if (closest_obj_index != NOT_SET)
		{
			hit_material = objects[closest_obj_index].material;
			if (hit_material.transmittance <= 0)
				light_intensity = compute_light(scene, lights, objects, meshes_info,
						polygons, vertices, v_normals, &best_hit, &ray, &hit_material);
			result_color += ray.energy
					* light_intensity
					* shade(&ray, &best_hit, &hit_material);
		}
		else if (closest_polygon_index != NOT_SET)
		{
			t_material	polygon_material = get_polygon_material(meshes_info, polygons, closest_polygon_index);
			if (polygon_material.transmittance <= 0)
				light_intensity = compute_light(scene, lights, objects, meshes_info,
						polygons, vertices, v_normals, &best_hit, &ray, &polygon_material);
			result_color += ray.energy * light_intensity
					* shade(&ray, &best_hit, &polygon_material);
		}
		else
		{
			ray.energy = 0;
			result_color = get_float3_color(COL_BG);
		}
		if (!ray_has_energy(&ray))
			break;
	}
	return result_color;
}