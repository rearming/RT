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

	a = dot(ray->dir, ray->dir) - dot_ray_axis_paraboloid
			* dot_ray_axis_paraboloid;
	b = 2.f * (dot(ray->dir, origin_center) - dot_ray_axis_paraboloid *
			(dot_origin_center_axis_paraboloid + 2.f * paraboloid->distance));
	c = dot(origin_center, origin_center) - dot_origin_center_axis_paraboloid
			* (dot_origin_center_axis_paraboloid + 4.f * paraboloid->distance);

	discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;

	float root = (-b - sqrt(discriminant)) / (2.f * a);
	float root2 = (-b + sqrt(discriminant)) / (2.f * a);
	if (root < 0 || (root > root2 && root2 > 0))
		root = root2; // пересечение перед камерой, берем меньший (ближайший)

	if (root < best_hit->distance && root > RAY_MIN_EPSILON && root > 0)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		const float dot_center_pos_axis = dot(best_hit->pos
				- paraboloid->center, paraboloid->axis);
		best_hit->normal = fast_normalize(best_hit->pos - paraboloid->center
				- paraboloid->axis * (dot_center_pos_axis
				+ paraboloid->distance));
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

	const float 	a = 4.f * radius_pow_2 * dot(ray->dir, ray->dir)
						- a_1 * a_1;
	const float 	b = 2.f * (4.f * radius_pow_2 * dot(ray->dir, origin_center)
						- a_1 * a_2);
	const float 	c = 4.f * radius_pow_2 * dot(origin_center, origin_center)
						- a_2 * a_2;

	float			discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;
	discriminant = sqrt(discriminant);

	const float		x = (-b - discriminant) / (2.f * a);
	const float		x2 = (-b + discriminant) / (2.f * a);
	const float		root = min(x, x2);
	const float		root2 = max(x, x2);
	const float3	pos_root = ray->origin + root * ray->dir;
	const float3	pos_root2 = ray->origin + root2 * ray->dir;

	if (root > RAY_MIN_EPSILON)
	{
		if (root < best_hit->distance && root > RAY_MIN_EPSILON)
		{
			best_hit->distance = root;
			best_hit->pos = pos_root;
			float		pos_f1 = length(pos_root - ellipsoid->center);
			best_hit->normal = fast_normalize(pos_root - (ellipsoid->center
					+ ellipsoid->axis * (ellipsoid->distance
					* ellipsoid->distance * pos_f1 / ellipsoid->radius)));
			return true;
		}
	}
	else if (root2 > RAY_MIN_EPSILON)
	{
		const float 	dot_o_c_axis = dot(origin_center, ellipsoid->axis);
		if (dot_o_c_axis > ellipsoid->distance - ellipsoid->radius
				&& dot_o_c_axis > ellipsoid->distance + ellipsoid->radius / 2)
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->normal = -ray->dir;
			best_hit->pos = ray->origin + RAY_MIN_EPSILON * ray->dir;
			return true;
		}
	}
	return false;
}
