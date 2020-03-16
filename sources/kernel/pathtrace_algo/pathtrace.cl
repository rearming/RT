
float3		pathtrace(
		__global const t_scene *scene,
		__global const t_object *objects,
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
		int depth,
		float *seed,
		float2 pixel)
{
	float3		result_color = (float3)(0);
	t_rayhit	hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
	int			closest_obj_index;
	int			closest_polygon_index;

	for (int i = 0; i < params->pathtrace_params.max_depth; ++i)
	{
		hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
		closest_intersection(scene, objects, kd_info, kd_tree, kd_indices, polygons, vertices, v_normals, &ray, &hit, &closest_polygon_index, &closest_obj_index);

		t_material	hit_material;
		if (get_hit_material(&hit_material, objects, meshes_info, polygons, vertices, v_normals, v_textures, closest_obj_index, closest_polygon_index))
		{
#ifdef RENDER_TEXTURES
			if (hit_material.texture_number >= 0)
				result_color += ray.energy * texture_shade_pathtrace(&texture_info[hit_material.texture_number],
						texture_list, &objects[closest_obj_index], &ray, &hit, hit_material, seed, pixel);
			else
#endif
		result_color += ray.energy * shade_pathtrace(&ray, &hit, hit_material, seed, pixel);
		}
		else
		{
#ifdef RENDER_TEXTURES
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