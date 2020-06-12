bool				ray_sphere_intersect_cut(
		t_ray *ray,
		__global const t_object *sphere,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - sphere->center;
	const float 	dot_ray_axis_sphere = dot(ray->dir, sphere->axis);

	const float	a = dot(ray->dir, ray->dir);
	const float	b = 2.f * dot(origin_center, ray->dir);
	const float	c = dot(origin_center, origin_center) - sphere->radius
			* sphere->radius;

	const float		inter = -dot(origin_center - (sphere->len - sphere->radius)
			* sphere->axis, sphere->axis) / dot_ray_axis_sphere;

	float	discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;
	discriminant = sqrt(discriminant);

	const float x1 = (-b - discriminant) / (2.f * a);
	const float x2 = (-b + discriminant) / (2.f * a);
	const float	root = min(x1, x2);
	const float	root2 = max(x1, x2);

	if (root > 0 && root2 > 0)
	{
		if (dot(origin_center + ray->dir * root, sphere->axis)
				< (sphere->len - sphere->radius))
		{
			if (root < best_hit->distance)
			{
				best_hit->distance = root;
				best_hit->pos = ray->origin + root * ray->dir;
				best_hit->normal = fast_normalize(best_hit->pos - sphere->center);
				return true;
			}
		}
		else
		{
			if (dot(origin_center + ray->dir * root2, sphere->axis)
						< (sphere->len - sphere->radius)
					&& inter < best_hit->distance)
			{
				best_hit->distance = inter;
				best_hit->pos = ray->origin + ray->dir * inter;
				best_hit->normal = sphere->axis;
				return true;
			}
		}
	}
	else if (root2 > 0)
	{
		if (dot(origin_center, sphere->axis) < (sphere->len - sphere->radius))
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->pos = ray->origin - ray->dir * RAY_MIN_EPSILON ;
			best_hit->normal = -ray->dir;
			return true;
		}
		else
		{
			if (dot(origin_center + ray->dir * root2, sphere->axis)
				< (sphere->len - sphere->radius) && inter < best_hit->distance)
			{
				best_hit->distance = inter;
				best_hit->pos = ray->origin + ray->dir * inter;
				best_hit->normal = sphere->axis;
				return true;
			}
		}
	}
	return false;
}

bool				ray_paraboloid_intersect_cut(
		t_ray *ray,
		__global const t_object *paraboloid,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - paraboloid->center;
	const float		dot_origin_center_axis_paraboloid = dot(origin_center,
													   paraboloid->axis);
	const float		dot_ray_axis_paraboloid = dot(ray->dir, paraboloid->axis);
	float			discriminant;
	const float		a = dot(ray->dir, ray->dir) - dot_ray_axis_paraboloid
			* dot_ray_axis_paraboloid;
	const float		b = 2.f * (dot(ray->dir, origin_center)
			- dot_ray_axis_paraboloid * (dot_origin_center_axis_paraboloid
			+ 2.f * paraboloid->distance));
	const float		c = dot(origin_center, origin_center)
			- dot_origin_center_axis_paraboloid
			* (dot_origin_center_axis_paraboloid + 4.f * paraboloid->distance);

	discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;
	discriminant = sqrt(discriminant);

	const float 	x1 = (-b - discriminant) / (2.f * a);
	const float 	x2 = (-b + discriminant) / (2.f * a);
	const float 	root = min(x1, x2);
	const float		root2 = max(x1, x2);
	const float3	pos_root = ray->origin + root * ray->dir;
	const float3	pos_root2 = ray->origin + root2 * ray->dir;
	float			sqr_dist_origin_axis = (dot(origin_center, origin_center)
							- dot_origin_center_axis_paraboloid
								* dot_origin_center_axis_paraboloid);
	sqr_dist_origin_axis *= sqr_dist_origin_axis * paraboloid->distance;

	if (sqr_dist_origin_axis > dot_origin_center_axis_paraboloid
			|| dot_origin_center_axis_paraboloid < 0)
	{
		if (dot(pos_root - paraboloid->center, paraboloid->axis)
				< paraboloid->len)
		{
			if (root < best_hit->distance && root > RAY_MIN_EPSILON)
			{
				best_hit->distance = root;
				best_hit->pos = pos_root;
				best_hit->normal = fast_normalize(best_hit->pos
						- paraboloid->center - paraboloid->axis
						* (dot(best_hit->pos - paraboloid->center,
								paraboloid->axis) + paraboloid->distance));
				return true;
			}
		}
		else
		{
			if (dot(pos_root2 - paraboloid->center, paraboloid->axis)
					< paraboloid->len)
			{
				const float3		origin_center_plane = ray->origin
						- paraboloid->center - paraboloid->axis
						* paraboloid->len;
				const float		intersect_dist = (-dot(origin_center_plane,
						paraboloid->axis)) / (dot_ray_axis_paraboloid);
				if (intersect_dist < best_hit->distance
						&& intersect_dist > RAY_MIN_EPSILON)
				{
					best_hit->distance = intersect_dist;
					best_hit->normal = paraboloid->axis;
					best_hit->pos = ray->origin + intersect_dist * ray->dir;
					return true;
				}
			}
		}
	}
	else
	{
		if (dot_origin_center_axis_paraboloid > paraboloid->len)
		{
			if (root2 > 0)
			{
				if (dot((root > 0 ? pos_root : pos_root2) - paraboloid->center,
						paraboloid->axis) < paraboloid->len)
				{
					const float3		origin_center_plane = ray->origin
										- paraboloid->center - paraboloid->axis
											* paraboloid->len;
					const float		intersect_dist = (-dot(origin_center_plane,
									paraboloid->axis)) / (dot_ray_axis_paraboloid);
					if (intersect_dist < best_hit->distance
							&& intersect_dist > RAY_MIN_EPSILON)
					{
						best_hit->distance = intersect_dist;
						best_hit->normal = paraboloid->axis;
						best_hit->pos = ray->origin + intersect_dist * ray->dir;
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool				ray_ellipsoid_intersect_cut(	/// TODO debag needed
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

	if (root > 0)
	{
		if (dot(pos_root - ellipsoid->center, ellipsoid->axis)
				< (ellipsoid->len - ellipsoid->distance + ellipsoid->radius))
		{
			if (root < best_hit->distance && root > RAY_MIN_EPSILON && root > 0)
			{
				best_hit->distance = root;
				best_hit->pos = pos_root;
														///сложная формула
//				const float3	center_mid_pos = (best_hit->pos + (ellipsoid->center
//						+ ellipsoid->axis * ellipsoid->distance * 0.5f));
//				best_hit->normal = fast_normalize(center_mid_pos + ellipsoid->axis
//						* (1 - b * b / (4 * a * a)) * dot(center_mid_pos,
//								ellipsoid->axis));
				float		pos_f1 = length(pos_root - ellipsoid->center);
				best_hit->normal = fast_normalize(pos_root - (ellipsoid->center
						+ ellipsoid->axis * (ellipsoid->distance
						* ellipsoid->distance * pos_f1 / ellipsoid->radius)));
				return true;
			}
		}
		else
		{
			if (dot(pos_root2 - ellipsoid->center, ellipsoid->axis)
					< (ellipsoid->len - ellipsoid->distance
						+ ellipsoid->radius))
			{
				const float3	origin_center_plane = ray->origin
						- ellipsoid->center - ellipsoid->axis
						* (ellipsoid->len - ellipsoid->distance + ellipsoid->radius);
				const float		intersect_dist = (-dot(origin_center_plane,
						ellipsoid->axis)) / (dot(ray->dir, ellipsoid->axis));
				if (intersect_dist < best_hit->distance
						&& intersect_dist > RAY_MIN_EPSILON)
				{
					best_hit->distance = intersect_dist;
					best_hit->normal = ellipsoid->axis;
					best_hit->pos = ray->origin + intersect_dist * ray->dir;
					return true;
				}
			}
		}
	}
	else if (root2 > 0)
	{
		const float 	dot_o_c_axis = dot(origin_center, ellipsoid->axis);
		if (dot_o_c_axis > ellipsoid->distance - ellipsoid->radius
				&& dot_o_c_axis > ellipsoid->distance + ellipsoid->radius / 2
				&& dot_o_c_axis < (ellipsoid->len - ellipsoid->distance + ellipsoid->radius))
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->normal = -ray->dir;
			best_hit->pos = ray->origin + RAY_MIN_EPSILON * ray->dir;
			return true;
		}
	}
	return false;
}