
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
			/// сфера, параболоид и эллипсоид разделен на обрезанные и не обрезанные
				case (SPHERE):
					if ((objects[i].len >= 0) ?
							ray_sphere_intersect_cut(ray, &objects[i], out_best_hit)
							: ray_sphere_intersect(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (PLANE):
					if (ray_plane_intersect(ray, objects[i].center,
							objects[i].normal, out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (CONE):
					if (ray_cone_intersect(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (CYLINDER):
					if (ray_cylinder_intersect(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (TRIANGLE):
					if (ray_triangle_intersect_MT(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (PARABOLOID):
					if ((objects[i].len > 0) ?
							ray_paraboloid_intersect_cut(ray, &objects[i], out_best_hit)
							: ray_paraboloid_intersect(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (ELLIPSOID):
					if ((objects[i].len >= 0) ?
							ray_ellipsoid_intersect_cut(ray, &objects[i], out_best_hit)
							: ray_ellipsoid_intersect(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				case (AABB):
					if (ray_aabb_intersection(ray, &objects[i], out_best_hit))
						*out_closest_obj_index = i;
					break;
				default :
					if (objects[i].type == BOX || objects[i].type == CAPSULE
							|| objects[i].type == TORUS
							|| objects[i].type == ELLIPSOID_RAYMARCH
							|| objects[i].type == TORUS_CAPPED
							|| objects[i].type == HEX_PRISM
							|| objects[i].type == ROUND_CONE)
						if(ray_march(ray, &objects[i], out_best_hit))
							*out_closest_obj_index = i;
					break;
			}
		}
#endif // RENDER_OBJECTS

#ifdef RENDER_MESH
*out_closest_polygon_index = kd_tree_traverse(kd_info, kd_tree, kd_indices, polygons, vertices, v_normals, ray, out_best_hit);
//	*out_closest_polygon_index = ray_mesh_intersect(&scene->meshes, polygons, vertices, v_normals, ray, out_best_hit);
	if (isset(*out_closest_polygon_index))
		*out_closest_obj_index = NOT_SET;
#endif

#ifdef RENDER_RAYMARCH
//for (int i = 0; i < scene->obj_nbr; i++)
//	if (ray_march(ray, &objects[i], out_best_hit))
//		*out_closest_obj_index = i;
	//// крайне неоптимально реализована функция,
	//// свич происходит на каждом шаге реймарша
#endif
}
