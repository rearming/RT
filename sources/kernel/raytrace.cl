
float3		shade(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		__global const t_texture_info *texture_info,
		__global const int *texture_list,
		__global const t_object *object)
{
	float3	diffuse_color = material->diffuse;

	if (material->transmittance <= 0) // if not transmit
	{
#ifdef RENDER_TEXTURES
		if (material->texture_number != NOT_SET)
				diffuse_color = texture(ray, hit, &texture_info[material->texture_number], texture_list, object);
#endif
		ray->origin = hit->pos + hit->normal * RT_EPSILON;
		ray->dir = reflect(ray->dir, hit->normal);
		ray->energy *= material->specular; // if material is diffuse -> material->specular == 0 -> energy = 0;
	}
	else
	{
		ray->origin = hit->pos;
		ray->dir = convex_refract(ray->dir, hit->normal, material->refraction);
		ray->energy *= material->specular;
	}
#ifdef RENDER_TEXTURES
	if (material->texture_number != NOT_SET)
		return diffuse_color;
#endif
	return material->emission_power > 0 ? material->emission_color : diffuse_color;
}

float3		raytrace(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_light *lights,
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		__global const float3 *v_textures,
		__global const t_render_params *params,
		__global const t_texture_info *texture_info,
		__global const int *texture_list,
		__global const float3 *skybox_list,
		__global const t_skybox_info *skybox_info,
		t_ray ray,
		float *out_intersection_distance)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit;
	int			closest_obj_index;
	int			closest_polygon_index;

	for (int i = 0; i < params->raytrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, kd_info, kd_tree, kd_indices, polygons, vertices, v_normals, &ray, &best_hit, &closest_polygon_index, &closest_obj_index);
		if (i == 0)
			*out_intersection_distance = best_hit.distance;
		t_material	hit_material;
		if (get_hit_material(&hit_material, objects, meshes_info, polygons, vertices, v_normals, v_textures, closest_obj_index, closest_polygon_index))
		{
			result_color += ray.energy
				* compute_light(scene, lights, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, v_textures, &best_hit, &ray, &hit_material)
				* shade(&ray, &best_hit, &hit_material, texture_info, texture_list, &objects[closest_obj_index]);
		}
		else
		{
#ifdef RENDER_SKYBOX
			result_color += ray.energy * skybox_color(skybox_list, skybox_info, skybox_normal(ray));
#else
			result_color += ray.energy * get_float3_color(COL_BG);
#endif
			ray.energy = 0;
		}
		if (!ray_has_energy(&ray))
			break;
	}
	return result_color;
}