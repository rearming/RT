t_bool				ray_plane_intersect(
		t_ray *ray,
		float3 center,
		float3 normal,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - center;

	float intersect_dist = (-dot(origin_center, normal)) / dot(ray->dir, normal);
	if (intersect_dist < best_hit->distance && intersect_dist > 0)
	{
		best_hit->distance = intersect_dist;
		best_hit->normal = normal;
		best_hit->pos = ray->origin + intersect_dist * ray->dir;
		return true;
	}
	return false;
}

t_bool				ray_sphere_intersect(
		t_ray *ray,
		__constant t_object *sphere,
		t_rayhit *out_best_hit)
{
	const float3	origin_center = ray->origin - sphere->center;
	float 			a, b, c, discriminant;

	a = dot(ray->dir, ray->dir);
	b = 2 * dot(origin_center, ray->dir);
	c = dot(origin_center, origin_center) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return false;

	float root = (-b - sqrt(discriminant)) / (2 * a);

	if (root < out_best_hit->distance) /// может нужна проверка на root < 0? проверить!
	{
		out_best_hit->distance = root;
		out_best_hit->pos = ray->origin + root * ray->dir;
		out_best_hit->normal = fast_normalize(out_best_hit->pos - sphere->center);
		return true;
	}
	return false;
}
