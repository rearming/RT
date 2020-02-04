
float3		shade(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		__constant t_object *object)
{
	if (hit->distance < INFINITY)
	{
		float3	diffuse_color = material->diffuse;

		if (material->transmittance <= 0)
		{
			if (object && material->texture_number >= 0 && material->texture_number < TEXTURE_NUM)
				diffuse_color = texture(out_ray, hit, &texture_info[material->texture_number], texture_list, object);
			ray->origin = hit->pos + hit->normal * RT_EPSILON;
			ray->dir = reflect(ray->dir, hit->normal);
			ray->energy *= material->specular;
		}
		else
		{
			ray->origin = hit->pos;
			ray->dir = convex_refract(ray->dir, hit->normal, material->refraction);
			ray->energy *= material->specular;
		}
		return material->emission_power > 0 ? material->emission_color : diffuse_color;
	}
	else
	{
		ray->energy = 0;
		return get_float3_color(COL_BG);
	}
}

float3		raytrace(
		__global const t_scene *scene,
#ifdef RENDER_OBJECTS
		__global const t_object *objects,
#endif
		__global const t_light *lights,
#ifdef RENDER_MESH
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
# ifdef RENDER_MESH_VTEXTURES
		__global const float3 *v_textures,
# endif
#endif
		__global const t_renderer_params *params,
		__global t_texture_info *texture_info,
		__global float *texture_list,
		t_ray ray)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit;
	int			closest_obj_index;
	int			closest_polygon_index;

	for (int i = 0; i < params->raytrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene,
#ifdef RENDER_OBJECTS
				objects,
#endif // RENDER_OBJECTS
#ifdef RENDER_MESH
		polygons, vertices, v_normals,
#endif
		&ray, &best_hit, &closest_polygon_index, &closest_obj_index);
		float		light_intensity = 0;
		t_material	hit_material;
#ifdef RENDER_OBJECTS
		if (closest_obj_index != NOT_SET)
		{
			hit_material = objects[closest_obj_index].material;
			if (hit_material.transmittance <= 0)
				light_intensity = compute_light(scene, lights, objects,
# ifdef RENDER_MESH
						meshes_info,
						polygons, vertices, v_normals,
# endif // RENDER_MESH
						&best_hit, &ray, &hit_material);
			result_color += ray.energy
					* light_intensity
					* shade(&ray, &best_hit, &hit_material, texture_info, texture_list, &objects[closest_obj_index]);
		}
# ifdef RENDER_MESH
		else //чтобы else был только когда (RENDER_OBJECTS | RENDER_MESH)
# endif
#endif // RENDER_OBJECTS
#ifdef RENDER_MESH
			if (closest_polygon_index != NOT_SET)
		{
			t_material	polygon_material = get_polygon_material(meshes_info, polygons, closest_polygon_index);
			if (polygon_material.transmittance <= 0)
				light_intensity = compute_light(scene, lights,
# ifdef RENDER_OBJECTS
						objects,
# endif
						meshes_info,
						polygons, vertices, v_normals, &best_hit, &ray, &polygon_material);
			result_color += ray.energy
					* light_intensity
					* shade(&ray, &best_hit, &polygon_material, texture_info, texture_list, 0);
		}
#endif // RENDER_MESH
		else
		{
			result_color += ray.energy * skybox_color(&texture_info[0], texture_list, skybox_normal(ray));
			ray.energy = 0;
		}
		if (!ray_has_energy(&ray))
			break;
	}
	return result_color;
}