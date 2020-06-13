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
		best_hit->normal = ray_dir_dot_normal > 0 ? normal * -1.f : normal;
			/// фикс для того, чтобы plane не просвечивал
			/// (нормаль зависит от того, с какой стороны камера)
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

	const float	a = dot(ray->dir, ray->dir);
	const float	b = 2.f * dot(origin_center, ray->dir);
	const float	c = dot(origin_center, origin_center) - sphere->radius
			* sphere->radius;

	float	discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;
	discriminant = sqrt(discriminant);

	const float x1 = (-b - discriminant) / (2.f * a);
	const float x2 = (-b + discriminant) / (2.f * a);
	const float	root = min(x1, x2);
	const float	root2 = max(x1, x2);

	if (root < 0 && root2 < 0)
		return false;
	if (root < best_hit->distance && root > RAY_MIN_EPSILON)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		best_hit->normal = fast_normalize(best_hit->pos - sphere->center);
		return true;
	}
	return false;
}

bool				ray_cone_intersect(
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
		if (cone->len <= 0 || (cone->len > 0 && fabs(dot(cone->axis, ray->origin + near * ray->dir - cone->center)) < cone->len))
		{
			if (fabs(dot(fast_normalize(origin_center), cone->axis))
									< cos(atan(tan_halfangle_of_cone)))
			{
				const float3 cone_forming = fast_normalize(origin_center + near
											* ray->dir);
					/// вектор прямой направляющей конуса на которой лежит pos
				best_hit->distance = near;
				best_hit->pos = ray->origin + near * ray->dir;
				best_hit->normal = fast_normalize(dot(cone->axis, cone_forming) > 0 ?
										cone_forming - cone->axis :
										cone->axis + cone_forming);
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
		else if (fabs(dot(cone->axis, origin_center + far * ray->dir)) <= cone->len)
		{
			if (fabs(dot(fast_normalize(origin_center), cone->axis))
						< cos(atan(tan_halfangle_of_cone)))
			{
				const float3 cone_forming = fast_normalize(origin_center + far
												* ray->dir);
				return (ray_plane_intersect(ray,
							dot(cone->axis, cone_forming) > 0 ?
							(cone->center + cone->len * cone->axis )
							: (cone->center - cone->len * cone->axis ),
							cone->axis,
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
			&& near < 0 && fabs(dot(origin_center, cone->axis)) <= cone->len
			&& acos(fabs(dot(fast_normalize(origin_center), cone->axis)))
				<= cone->angle * M_PI_360)
	{
		best_hit->distance = RAY_MIN_EPSILON;
		best_hit->pos = ray->origin - ray->dir * RAY_MIN_EPSILON ;
		best_hit->normal = -ray->dir;
		return true;
	}
	return false;
}

bool		ray_cylinder_intersect(
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
			* dot_origin_center_axis < cylinder->radius * cylinder->radius)
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