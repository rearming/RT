bool				ray_sphere_intsect_cut(
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

	if (root > RAY_MIN_EPSILON && root2 > RAY_MIN_EPSILON)
	{
		if (dot(origin_center + ray->dir * root, sphere->axis) + RAY_MIN_EPSILON <= (sphere->len - sphere->radius))
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
			if (dot(origin_center + ray->dir * root2, sphere->axis) + RAY_MIN_EPSILON < (sphere->len - sphere->radius)
					&& inter < best_hit->distance)
			{
				best_hit->distance = inter;
				best_hit->pos = ray->origin + ray->dir * inter;
				best_hit->normal = sphere->axis;
				return true;
			}
		}
	}
	else if (root2 > RAY_MIN_EPSILON)
	{
		if (dot(origin_center, sphere->axis) + RAY_MIN_EPSILON < (sphere->len
				- sphere->radius))
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->pos = ray->origin - ray->dir * RAY_MIN_EPSILON ;
			best_hit->normal = -ray->dir;
			return true;
		}
		else
		{
			if (dot(origin_center + ray->dir * root2, sphere->axis) + RAY_MIN_EPSILON
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

bool				ray_ellipsoid_intersect_cut(
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

bool				ray_cone_intersect_cut(
		t_ray *ray,
		__global const t_object *cone,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - cone->center;
	const float		dot_origin_center_axis_cone = dot(origin_center, cone->axis);
	const float		dot_ray_axis_cone = dot(ray->dir, cone->axis);
	const float		tan_halfangle_of_cone = tan(cone->angle * M_PI_360);
					/// угол в градусах, преобразуем в радианы для tan()
	const float		one_sqr_tan_halfangle_of_cone = tan_halfangle_of_cone
											* tan_halfangle_of_cone + 1.f;
	///1 + квадрат тангенса полугла вершины конуса,

	const float		a = dot(ray->dir, ray->dir) - dot_ray_axis_cone
			* dot_ray_axis_cone * one_sqr_tan_halfangle_of_cone;
	const float		b = 2.f * (dot(origin_center, ray->dir) - dot_ray_axis_cone
			* dot_origin_center_axis_cone * one_sqr_tan_halfangle_of_cone);
	const float		c = dot(origin_center, origin_center)
			- dot_origin_center_axis_cone * dot_origin_center_axis_cone
			* one_sqr_tan_halfangle_of_cone;
	float discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;
	else
		discriminant = sqrt(discriminant);

	const float	x1 = (-b - discriminant) / (2 * a);
	const float	x2 = (-b + discriminant) / (2 * a);
	const float 	near = min(x1, x2) < 0 ? max(x1, x2) : min(x1, x2);
	const float 	far = max(x1, x2);
	if (near < best_hit->distance && near > RAY_MIN_EPSILON && near > 0)
	{
			// проверка на нахождение внутри
		if (fabs(dot(origin_center, cone->axis)) <= cone->len
				&& acos(fabs(dot(fast_normalize(origin_center), cone->axis)))
					<= cone->angle * M_PI_360)
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->pos = ray->origin - ray->dir * RAY_MIN_EPSILON ;
			best_hit->normal = -ray->dir;
			return true;
		}
		if (cone->len == NOT_SET || (fabs(dot(cone->axis, ray->origin + near
				* ray->dir - cone->center)) + RAY_MIN_EPSILON < cone->len))
		{
			if (fabs(dot(fast_normalize(origin_center), cone->axis))
									< cos(atan(tan_halfangle_of_cone)))
			{
				const float3 cone_forming = fast_normalize(origin_center + near
											* ray->dir);
					/// вектор прямой направляющей конуса на которой лежит pos
				best_hit->distance = near;
				best_hit->pos = ray->origin + near * ray->dir;
				best_hit->normal = fast_normalize(
						dot(cone->axis, cone_forming) > 0 ?
						cone_forming - cone->axis : cone->axis + cone_forming);
				return true;
			}
			else
			{
				const float3 cone_forming = fast_normalize(origin_center
						+ near * ray->dir);
				return (ray_plane_intersect(ray,
							dot(cone->axis, cone_forming) > 0 ?
							(cone->center + cone->len * cone->axis )
							: (cone->center - cone->len * cone->axis ),
							cone->axis,
							best_hit));
			}
		}
		else if (fabs(dot(cone->axis, origin_center + far * ray->dir)) + RAY_MIN_EPSILON <= cone->len)
		{
			if (fabs(dot(fast_normalize(origin_center), cone->axis) + RAY_MIN_EPSILON)
					< cos(atan(tan_halfangle_of_cone)))
			{
				const float3 cone_forming = fast_normalize(origin_center + far
												* ray->dir);
				return (ray_plane_intersect(ray, dot(cone->axis, cone_forming)
						> 0 ? (cone->center + cone->len * cone->axis )
						: (cone->center - cone->len * cone->axis ), cone->axis,
						best_hit));
			}
			else
			{
				const float3 cone_forming = fast_normalize(origin_center
										   + far * ray->dir);
					/// вектор прямой направляющей конуса на которой лежит pos

				best_hit->distance = far;
				best_hit->pos = ray->origin + far * ray->dir;
				best_hit->normal = fast_normalize(dot(cone->axis, cone_forming) > 0 ?
												  cone_forming - cone->axis :
												  cone->axis + cone_forming);
				return true;
			}
		}
	}
	else if (near < best_hit->distance && fabs(near) > RAY_MIN_EPSILON
			&& near < 0 && fabs(dot(origin_center, cone->axis)) + RAY_MIN_EPSILON
			<= cone->len && acos(fabs(dot(fast_normalize(origin_center),
			cone->axis)) + RAY_MIN_EPSILON) <= cone->angle * M_PI_360)
	{
		best_hit->distance = RAY_MIN_EPSILON;
		best_hit->pos = ray->origin - ray->dir * RAY_MIN_EPSILON ;
		best_hit->normal = -ray->dir;
		return true;
	}
	return false;
}

bool		ray_cylinder_intersect_cut(
		t_ray *ray,
		__global const t_object *cylinder,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - cylinder->center;
	const float		dot_origin_center_axis = dot(origin_center, cylinder->axis);
	const float		dot_ray_axis_cylinder = dot(ray->dir, cylinder->axis);

	const float		a = dot(ray->dir, ray->dir) - dot_ray_axis_cylinder
			* dot_ray_axis_cylinder;
	const float 	b = 2.f * (dot(ray->dir, origin_center)
			- dot_ray_axis_cylinder * dot_origin_center_axis);
	const float 	c = dot(origin_center, origin_center)
			- dot_origin_center_axis * dot_origin_center_axis
			- cylinder->radius * cylinder->radius;

	float	discriminant = b * b - 4.f * a * c;

	if (discriminant < 0)
		return false;
	discriminant = sqrt(discriminant);

	const float		root = (-b - discriminant) / (2.f * a);
	const float		root2 = (-b + discriminant) / (2.f * a);
	const float3	pos = ray->origin + root * ray->dir;
	const float3	pos2 = ray->origin + root2 * ray->dir;


	if (dot(origin_center, origin_center) - dot_origin_center_axis
			* dot_origin_center_axis + RAY_MIN_EPSILON < cylinder->radius * cylinder->radius)
	{
		if (cylinder->len == NOT_SET
				|| fabs(dot_origin_center_axis) < cylinder->len)
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->pos = ray->origin + ray->dir * RAY_MIN_EPSILON;
			best_hit->normal = -ray->dir;
			return true;
		}
		else
		{
			const float 	root2_hig = dot(pos2 - cylinder->center,
							   cylinder->axis);
			if ((dot_origin_center_axis > 0 && root2_hig < cylinder->len)
					|| (dot_origin_center_axis < 0
					&& root2_hig > -cylinder->len))
			{
				const float hit_plane = (-dot(ray->origin - (cylinder->center
						+ ((dot_origin_center_axis > 0 ? cylinder->len
						: -cylinder->len) * cylinder->axis)), cylinder->axis))
						/ dot_ray_axis_cylinder;
				if (best_hit->distance > hit_plane)
				{
					best_hit->distance = hit_plane;
					best_hit->pos = ray->origin + hit_plane * cylinder->axis;
					best_hit->normal = dot_origin_center_axis > 0 ?
							cylinder->axis : -cylinder->axis;
					return true;
				}
			}
			return false;
		}
	}
	if (root > RAY_MIN_EPSILON)
	{
		const float3	pos_center = pos - cylinder->center;
		const float 	root_hig = dot(pos_center, cylinder->axis);
		if (cylinder->len == NOT_SET || (root_hig < cylinder->len
				&& root_hig > -cylinder->len))
		{
			if (best_hit->distance > root)
			{
				best_hit->distance = root;
				best_hit->pos = pos;
				best_hit->normal = fast_normalize(pos_center
						- root_hig * cylinder->axis);
				return true;
			}
		}
		else
		{
			const float 	root2_hig = dot(pos2 - cylinder->center,
					cylinder->axis);
			if ((root_hig > cylinder->len && root2_hig < cylinder->len) ||
					(root_hig < -cylinder->len && root2_hig > -cylinder->len))
			{
				const float hit_plane = (-dot(ray->origin - (cylinder->center
						+ ((root_hig < 0 ? -cylinder->len : cylinder->len)
						* cylinder->axis)), cylinder->axis))
						/ dot_ray_axis_cylinder;
				if (best_hit->distance > hit_plane)
				{
					best_hit->distance = hit_plane;
					best_hit->pos = ray->origin + hit_plane * cylinder->axis;
					best_hit->normal = root_hig > 0 ?
									 cylinder->axis : -cylinder->axis;
					return true;
				}
			}
		}
	}
	return false;
}