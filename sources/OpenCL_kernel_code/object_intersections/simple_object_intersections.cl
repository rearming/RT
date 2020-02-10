bool				ray_plane_intersect(
		t_ray *ray,
		float3 center,
		float3 normal,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - center;
	const float		ray_dir_dot_normal = dot(ray->dir, normal);
	if (ray_dir_dot_normal == 0) /// луч параллелен плоскости
		return false;
	const float		intersect_dist = (-dot(origin_center, normal)) / ray_dir_dot_normal;

	if (intersect_dist < best_hit->distance && intersect_dist > RAY_MIN_EPSILON)
	{
		best_hit->distance = intersect_dist;
		best_hit->normal = ray_dir_dot_normal > 0 ? normal * -1 : normal;
//		best_hit->normal = normal;
		///фикс для того, чтобы plane не просвечивал (нормаль зависит от того, с какой стороны камера)
		best_hit->pos = ray->origin + intersect_dist * ray->dir;
		return true;
	}
	return false;
}

bool				ray_sphere_intersect(
		t_ray *ray,
		__global const t_object *sphere,
		t_rayhit *best_hit)
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
//	float root2 = (-b + sqrt(discriminant)) / (2 * a);
	// todo пофиксить так чтобы не видеть изнутри объектов через них

	if (root < best_hit->distance && root > RAY_MIN_EPSILON)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		best_hit->normal = fast_normalize(best_hit->pos - sphere->center);
		return true;
	}
	return false;
}
