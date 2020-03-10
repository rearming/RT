


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
		__global const t_renderer_params *params,
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		t_ray ray)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit;
	int			closest_obj_index;
	int			closest_polygon_index;

	for (int i = 0; i < params->raytrace_params.max_depth; ++i)
	{
		best_hit = (t_rayhit){(float3)(0.0f), INFINITY, (float3)(0.0f)};
		closest_intersection(scene, objects, kd_info, kd_tree, kd_indices, polygons, vertices, v_normals, &ray, &best_hit, &closest_polygon_index, &closest_obj_index);

		t_material	hit_material;
		if (get_hit_material(&hit_material, objects, meshes_info, polygons, closest_obj_index, closest_polygon_index))
		{
			result_color += ray.energy
				* compute_light(scene, lights, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, &best_hit, &ray, &hit_material)
				* shade(&ray, &best_hit, &hit_material, texture_info, texture_list, &objects[closest_obj_index]);
		}
		else
		{
#ifdef RENDER_TEXTURES
			result_color += ray.energy * skybox_color(&texture_info[SKYBOX_NUM], texture_list, skybox_normal(ray));
#else
			result_color += ray.energy * get_float3_color(COL_BG);
#endif
			ray.energy = 0.0f;
		}
		if (!ray_has_energy(&ray))
			break;
	}
	return result_color;
}