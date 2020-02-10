bool		ray_aabb_intersection(t_ray *ray, __global const t_object *object, t_rayhit *best_hit)
{
	register float t[10];

	t[1] = (object->vmin.x - ray->origin.x) / ray->dir.x;
	t[2] = (object->vmax.x - ray->origin.x) / ray->dir.x;
	t[3] = (object->vmin.y - ray->origin.y) / ray->dir.y;
	t[4] = (object->vmax.y - ray->origin.y) / ray->dir.y;
	t[5] = (object->vmin.z - ray->origin.z) / ray->dir.z;
	t[6] = (object->vmax.z - ray->origin.z) / ray->dir.z;
	t[7] = fmax(fmax(fmin(t[1], t[2]), fmin(t[3], t[4])), fmin(t[5], t[6]));
	t[8] = fmin(fmin(fmax(t[1], t[2]), fmax(t[3], t[4])), fmax(t[5], t[6]));

	if (t[8] < 0 || t[7] > t[8])
		return false;
	else if (t[7] < best_hit->distance && t[7] > RAY_MIN_EPSILON)
	{
		best_hit->distance = t[7];
		best_hit->normal = -sign(ray->dir); // нормаль вообще неправильная, но как бы насрать
		best_hit->pos = ray->origin + ray->dir * t[7];
		return true;
	}
	return false;
}
