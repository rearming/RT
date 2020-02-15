
void				closest_intersection(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit,
		int *out_closest_polygon_index,
		int *out_closest_obj_index)
	{
		*out_closest_polygon_index = NOT_SET;
		*out_closest_obj_index = NOT_SET;
#ifdef RENDER_OBJECTS
		for (int i = 0; i < scene->obj_nbr; i++)
		{
			switch (objects[i].type)
			{
				case (SPHERE):
					if (ray_sphere_intersect(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (PLANE):
					if (ray_plane_intersect(ray, objects[i].center, objects[i].normal, out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (TRIANGLE):
					if (ray_triangle_intersect_MT(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (AABB):
					if (ray_aabb_intersection(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
			}
		}
#endif // RENDER_OBJECTS
#ifdef RENDER_MESH
		*out_closest_polygon_index = kd_tree_traverse(kd_info, kd_tree, kd_indices, polygons, vertices, v_normals, ray, out_best_hit);
//		*out_closest_polygon_index = ray_mesh_intersect(&scene->meshes, polygons, vertices, v_normals, ray, out_best_hit);
		if (isset(*out_closest_polygon_index))
			*out_closest_obj_index = NOT_SET;



#endif // RENDER_MESH
	}
