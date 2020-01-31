
void				closest_intersection(
		__constant t_scene *scene,
		__constant t_object *objects,
		t_ray *ray,
		t_rayhit *out_best_hit,
		int *out_closes_index)
{
	for (int i = 0; i < scene->obj_nbr; i++)
	{
		switch (objects[i].type)
		{
			case (SPHERE):
				if (ray_sphere_intersect(ray, &objects[i], out_best_hit))
					*out_closes_index = i;
				break ;
			case (PLANE):
				if (ray_plane_intersect(ray, objects[i].center, objects[i].normal, out_best_hit))
					*out_closes_index = i;
				break ;
		}
	}
}
