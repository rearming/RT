bool				ray_paraboloid_intersect(
		t_ray *ray,
		__global const t_object *paraboloid,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - paraboloid->center;
	const float		dot_origin_center_axis_paraboloid = dot(origin_center,
															   paraboloid->axis);
	const float		dot_ray_axis_paraboloid = dot(ray->dir, paraboloid->axis);

	float 			a, b, c, discriminant;

	a = dot(ray->dir, ray->dir) - dot_ray_axis_paraboloid * dot_ray_axis_paraboloid;
	b = 2.f * (dot(ray->dir, origin_center) - dot_ray_axis_paraboloid * (dot_origin_center_axis_paraboloid + 2.f * paraboloid->distance));
	c = dot(origin_center, origin_center) - dot_origin_center_axis_paraboloid * (dot_origin_center_axis_paraboloid + 4.f * paraboloid->distance);

	discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;

	float root = (-b - sqrt(discriminant)) / (2.f * a);
	float root2 = (-b + sqrt(discriminant)) / (2.f * a);
	if (root < 0 || (root > root2 && root2 > 0)) /// пересечение перед камерой,
	root = root2;								/// берем меньший (ближайший)

	if (root < best_hit->distance && root > RAY_MIN_EPSILON && root > 0)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		const float dot_center_pos_axis = dot(best_hit->pos - paraboloid->center, paraboloid->axis);
		best_hit->normal = fast_normalize(best_hit->pos - paraboloid->center
				- paraboloid->axis * (dot_center_pos_axis + paraboloid->distance));
		return true;
	}
	return false;
}

bool				ray_ellipsoid_intersect(
		t_ray *ray,
		__global const t_object *ellipsoid,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - ellipsoid->center;
	const float		radius_pow_2 = ellipsoid->radius * ellipsoid->radius;
	const float		distance_2 = ellipsoid->distance * 2;
	const float		a_1 = distance_2 * dot(ray->dir, ellipsoid->axis);
	const float		a_2 = radius_pow_2 + distance_2
			* dot(origin_center, ellipsoid->axis) - ellipsoid->distance;

	float 			a, b, c, discriminant;

	a = 4.f * radius_pow_2 * dot(ray->dir, ray->dir) - a_1 * a_1;
	b = 2.f * (4.f * radius_pow_2 * dot(ray->dir, origin_center) - a_1 * a_2);
	c = 4.f * radius_pow_2 * dot(origin_center, origin_center) - a_2 * a_2;

	discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;

	float root = (-b - sqrt(discriminant)) / (2.f * a);
	float root2 = (-b + sqrt(discriminant)) / (2.f * a);
	if (root < 0 || (root > root2 && root2 > 0)) /// пересечение перед камерой,
		root = root2;							/// берем меньший (ближайший)

	if (root < best_hit->distance && root > RAY_MIN_EPSILON && root > 0)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		const float3	center_mid_pos = (best_hit->pos + (ellipsoid->center
				+ ellipsoid->axis * ellipsoid->distance * 0.5f));
		best_hit->normal = fast_normalize(center_mid_pos + ellipsoid->axis
				* (1 - b * b / (4 * a * a)) * dot(center_mid_pos, ellipsoid->axis));
		return true;
	}
	return false;
}