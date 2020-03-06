
bool				find_any_intersection(
		__global __read_only const t_scene *scene,
		__global __read_only const t_object *objects,
		__global __read_only const t_kd_info *kd_info,
		__global __read_only const t_kd_arr_tree *kd_tree,
		__global __read_only const int *kd_indices,
		__global __read_only const t_mesh_info *meshes_info,
		__global __read_only const t_polygon *polygons,
		__global __read_only const float3 *vertices,
		__global __read_only const float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit)
{
	int		closest_polygon_index = NOT_SET;
	int		closest_obj_index = NOT_SET;

#ifdef RENDER_OBJECTS
	for (int i = 0; i < scene->obj_nbr; i++)
	{
		switch (objects[i].type)
		{
			case (SPHERE):
				if (ray_sphere_intersect(ray, &objects[i], out_best_hit))
					closest_obj_index = i;
				break;
			case (PLANE):
				if (ray_plane_intersect(ray, objects[i].center, objects[i].normal, out_best_hit))
					closest_obj_index = i;
				break;
			case (CONE):
				if (ray_cone_intersect(ray, &objects[i], out_best_hit))
					closest_obj_index = i;
				break;
			case (CYLINDER):
				if (ray_cylinder_intersect(ray, &objects[i], out_best_hit))
					closest_obj_index = i;
				break;
			case (TRIANGLE):
				if (ray_triangle_intersect_MT(ray, &objects[i], out_best_hit))
					closest_obj_index = i;
				break;
			case (PARABOLOID):
				if (ray_paraboloid_intersect(ray, &objects[i], out_best_hit))
					closest_obj_index = i;
				break;
			case (ELLIPSOID):
				if (ray_ellipsoid_intersect(ray, &objects[i], out_best_hit))
					closest_obj_index = i;
				break;
			case (AABB):
				if (ray_aabb_intersection(ray, &objects[i], out_best_hit))
					closest_obj_index = i;
				break;
		}
		if (isset(closest_obj_index))
			return true;
	}
#endif

#ifdef RENDER_MESH
	closest_polygon_index = kd_tree_traverse(kd_info, kd_tree, kd_indices, polygons, vertices, v_normals, ray, out_best_hit);
	return isset(closest_obj_index) || (isset(closest_polygon_index) && get_polygon_material(meshes_info, polygons, closest_polygon_index).transmittance <= 0);

#endif
	return isset(closest_obj_index);
}

bool				in_shadow(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_light_type light_type)
{
	t_rayhit	out_hit = {(float3)(0), 1, (float3)(0)};

	return find_any_intersection(scene, objects, kd_info, kd_tree, kd_indices,
			meshes_info, polygons, vertices, v_normals, ray, &out_hit);
}

float				blinn_phong_shine(float3 ray_dir, float3 light_dir, float3 normal, float phong_exp)
{
	float3	half_dir = normalize(ray_dir + light_dir);
	float	specular_angle = max(dot(half_dir, normal), 0.0f);
	return pow(specular_angle, phong_exp);
}

float				compute_light(
	__global __read_only const t_scene *scene,
	__global __read_only const t_light *lights,
	__global __read_only const t_object *objects,
	__global __read_only const t_kd_info *kd_info,
	__global __read_only const t_kd_arr_tree *kd_tree,
	__global __read_only const int *kd_indices,
	__global __read_only const t_mesh_info *meshes_info,
	__global __read_only const t_polygon *polygons,
	__global __read_only const float3 *vertices,
	__global __read_only const float3 *v_normals,
	t_rayhit *hit,
	t_ray *ray,
	t_material *hit_material)
{
	float		intensity = 0.0f;

	if (hit_material->transmittance > 0)
		return 0.0f;
	for (int i = 0; i < scene->lights_nbr; ++i)
	{
		float3		light_dir;

		if (lights[i].type == AMBIENT)
		{
			intensity = lights[i].intensity;
			continue;
		}
		else if (lights[i].type == POINT)
		{
			light_dir = lights[i].pos - hit->pos;
		}
		else if (lights[i].type == DIRECTIONAL)
		{
			light_dir = lights[i].dir;
		}
		t_ray	shadow_ray;
		shadow_ray.origin = hit->pos;
		shadow_ray.dir = light_dir;
		if (in_shadow(scene, objects, kd_info, kd_tree, kd_indices, meshes_info, polygons, vertices, v_normals, &shadow_ray, lights[i].type))
			continue;
		float	normal_dot_light = dot(hit->normal, light_dir);
		if (normal_dot_light > 0)
		{
			intensity += lights[i].intensity * normal_dot_light / (length(hit->normal) * length(light_dir));
			if (hit_material->phong_exp > 1)
				intensity += intensity * blinn_phong_shine(ray->dir, light_dir, hit->normal, hit_material->phong_exp);
		}
	}
	return intensity;
}
