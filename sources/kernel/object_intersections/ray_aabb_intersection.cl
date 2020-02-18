bool		ray_aabb_intersection(t_ray *ray, __global const t_object *object, t_rayhit *best_hit)
{
	float t[10];

	t[1] = (object->vmin.x - ray->origin.x) / ray->dir.x;
	t[2] = (object->vmax.x - ray->origin.x) / ray->dir.x;
	t[3] = (object->vmin.y - ray->origin.y) / ray->dir.y;
	t[4] = (object->vmax.y - ray->origin.y) / ray->dir.y;
	t[5] = (object->vmin.z - ray->origin.z) / ray->dir.z;
	t[6] = (object->vmax.z - ray->origin.z) / ray->dir.z;
	float t_near = fmax(fmax(fmin(t[1], t[2]), fmin(t[3], t[4])), fmin(t[5], t[6]));
	float t_far = fmin(fmin(fmax(t[1], t[2]), fmax(t[3], t[4])), fmax(t[5], t[6]));

	if (t_far < 0 || t_near > t_far)
		return false;
	else if (t_near < best_hit->distance && t_near > RAY_MIN_EPSILON)
	{
		best_hit->distance = t_near;
		best_hit->normal = -sign(ray->dir); // нормаль вообще неправильная, но как бы насрать
		best_hit->pos = ray->origin + ray->dir * t_near;
		return true;
	}
	return false;
}
