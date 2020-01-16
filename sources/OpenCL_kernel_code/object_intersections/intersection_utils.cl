void find_intersection(
		float3 origin,
		float3 ray_dir,
		__constant t_object *object,
		float *out_intersect1,
		float *out_intersect2)
{
	*out_intersect1 = INFINITY;
	*out_intersect2 = INFINITY;
	switch (object->type)
	{
		case (SPHERE):
			ray_sphere_intersect(origin, ray_dir, object, out_intersect1, out_intersect2);
			break ;
		case (PLANE):
			ray_plane_intersect(origin, ray_dir, object->center, object->normal, out_intersect1, out_intersect2);
			break ;
	}
}

void				closest_intersection(
		__constant t_scene *scene,
		__constant t_object *objects,
		t_ray ray,
		t_rayhit *best_hit,
		int *out_closest_obj_index)
{
	float		closest_intersect = INFINITY;
	float		intersect_1;
	float		intersect_2;

	for (int i = 0; i < scene->obj_nbr; i++)
	{
		find_intersection(ray.origin, ray.dir, &objects[i], &intersect_1, &intersect_2);
		if (in_range_inclusive(intersect_1, 0.01f, INFINITY) && intersect_1 < closest_intersect)
		{
			closest_intersect = intersect_1;
			*out_closest_obj_index = i;
		}
		if (in_range_inclusive(intersect_2, 0.01f, INFINITY) && intersect_2 < closest_intersect)
		{
			closest_intersect = intersect_2;
			*out_closest_obj_index = i;
		}
	}
	best_hit->distance = closest_intersect;
}
