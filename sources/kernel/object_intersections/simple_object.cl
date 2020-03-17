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
		///фикс для того, чтобы plane не просвечивал (нормаль зависит от того, с какой стороны камера)
		best_hit->pos = ray->origin + intersect_dist * ray->dir;
		return true;
	}
	return false;
}

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

	const float		inter = -dot(origin_center - sphere->len * sphere->axis,
										sphere->axis) / dot_ray_axis_sphere;

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
		if (dot(origin_center + ray->dir * root, sphere->axis) < sphere->len
				&& root < best_hit->distance)
		{
			best_hit->distance = root;
			best_hit->pos = ray->origin + root * ray->dir;
			best_hit->normal = fast_normalize(best_hit->pos - sphere->center);
			return true;
		}
		else
		{
			if (dot(origin_center + ray->dir * root2, sphere->axis) < sphere->len
					&& inter < best_hit->distance)
			{
				best_hit->distance = inter;
				best_hit->pos = ray->origin + ray->dir * inter;
				best_hit->normal = sphere->axis;
				return true;
			}
			else
				return false;
		}
	}
	else
	{
		if (dot(origin_center, sphere->axis) < sphere->len)
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->pos = ray->origin - ray->dir * RAY_MIN_EPSILON ;
			best_hit->normal = -ray->dir;
			return true;
		}
		else
		{
			if (dot(origin_center + ray->dir * root2, sphere->axis)
					< sphere->len && inter < best_hit->distance)
			{
				best_hit->distance = inter;
				best_hit->pos = ray->origin + ray->dir * inter;
				best_hit->normal = sphere->axis;
				return true;
			}
			else
				return false;
		}
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

	const float x1 = (-b - sqrt(discriminant)) / (2.f * a);
	const float x2 = (-b + sqrt(discriminant)) / (2.f * a);
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
	const float			tan_halfangle_of_cone = tan(cone->angle * M_PI_360);
					/// угол в градусах, преобразуем в радианы для tan()
	const float			one_sqr_tan_halfangle_of_cone = tan_halfangle_of_cone
											* tan_halfangle_of_cone + 1.f;
	///1 + квадрат тангенса полугла вершины конуса,

	const float	a = dot(ray->dir, ray->dir) - dot_ray_axis_cone * dot_ray_axis_cone
			* one_sqr_tan_halfangle_of_cone;
	const float	b = 2.f * (dot(origin_center, ray->dir) - dot_ray_axis_cone
			* dot_origin_center_axis_cone * one_sqr_tan_halfangle_of_cone);
	const float	c = dot(origin_center, origin_center) - dot_origin_center_axis_cone
			* dot_origin_center_axis_cone * one_sqr_tan_halfangle_of_cone;
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
			/// проверка на нахождение внутри
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

	const float	a = dot(ray->dir, ray->dir) - dot_ray_axis_cylinder
			* dot_ray_axis_cylinder;
	const float b = 2.f * (dot(ray->dir, origin_center) - dot_ray_axis_cylinder
			* dot_origin_center_axis);
	const float c = dot(origin_center, origin_center) - dot_origin_center_axis
			* dot_origin_center_axis - cylinder->radius
			* cylinder->radius;

	const float		distance_up = (-dot(ray->origin - (cylinder->center
			+ cylinder->len * cylinder->axis), cylinder->axis))
					/ dot_ray_axis_cylinder;
	const float		distance_down = (-dot(ray->origin - (cylinder->center
			- cylinder->len * cylinder->axis), -cylinder->axis))
					/ dot_ray_axis_cylinder;

	float	discriminant = b * b - 4.f * a * c;
	if (discriminant < 0)
		return false;

	discriminant = sqrt(discriminant);

	const float x1 = (-b - discriminant) / (2.f * a);
	const float x2 = (-b + discriminant) / (2.f * a);
	const float root = min(x1, x2);
	const float root2 = max(x1, x2);


	if (dot(origin_center, origin_center) - dot_origin_center_axis
					* dot_origin_center_axis < cylinder->radius
					* cylinder->radius)
		if (fabs(dot_origin_center_axis) < cylinder->len && cylinder->len > 0)
		{
			best_hit->distance = RAY_MIN_EPSILON;
			best_hit->pos = ray->origin - ray->dir * RAY_MIN_EPSILON ;
			best_hit->normal = -ray->dir;
			return true;
		}
		else if ((fabs(dot(origin_center + (root > 0 ? root : root2)
						* ray->dir, cylinder->axis))
					< cylinder->len && cylinder->len > 0)
					|| dot(origin_center + (root > 0 ? root : root2)
							* ray->dir, cylinder->axis)
						* dot_origin_center_axis < 0)
		{
			if (min(distance_up, distance_down) < best_hit->distance)
			{
				best_hit->distance = min(distance_up, distance_down);
				best_hit->pos = ray->origin + ray->dir * best_hit->distance;
				best_hit->normal = dot_ray_axis_cylinder < 0 ?
							   cylinder->axis : -1.f * cylinder->axis;
				return true;
			}
				else
					return false;
		}
		else
			return false;

	if ((root < RAY_MIN_EPSILON && root2 < RAY_MIN_EPSILON))
		return false;

	if (root > best_hit->distance)
		return false;

	if (fabs(dot(origin_center + root * ray->dir, cylinder->axis))
				< cylinder->len && cylinder->len > 0)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		best_hit->normal = fast_normalize(gram_schmidt_proc_r2(
				best_hit->pos - cylinder->center, cylinder->axis));
		///ортогонализация для R2 (процесс Грама-Шмидта) см. math_utils.cl
		return true;
	}
	else
	{
		if (((fabs(dot(origin_center + root2 * ray->dir, cylinder->axis))
						< cylinder->len && cylinder->len > 0)
					|| dot(origin_center + root2 * ray->dir,
							cylinder->axis) * dot(origin_center + root
							* ray->dir, cylinder->axis) < 0)
				&& min(distance_up, distance_down) < best_hit->distance)
		{
			best_hit->distance = min(distance_up, distance_down);
			best_hit->pos = ray->origin + best_hit->distance * ray->dir;
			best_hit->normal = dot_ray_axis_cylinder < 0 ? cylinder->axis
					: -1.f * cylinder->axis;
			return true;
		}
		else
			return false;
	}
}