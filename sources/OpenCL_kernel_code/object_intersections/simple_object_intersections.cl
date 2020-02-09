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
	float root2 = (-b + sqrt(discriminant)) / (2 * a);

	if (root < 0 || (root > root2 && root2 > 0)) /// пересечение перед камерой, берем меньший (ближайший)
	root = root2;
	if (root < best_hit->distance && root > RAY_MIN_EPSILON)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		best_hit->normal = fast_normalize(best_hit->pos - sphere->center);
		return true;
	}
	return false;
}

#define M_PI_360 0.00872664625997


// возвращает вектор равный вектору 1
// и перпендекулярный вектору 2 в плоскости векторов 1 и 2
float3	orthogonalization(float3 v1, float3 v2)
{
	return (v1 - v2 * dot(v1, v2) / dot(v2, v2)));
}


bool				ray_cone_intersect(
		t_ray *ray,
		__global const t_object *cone,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - cone->center;
	const float		dot_origin_center_and_axis_cone = dot(origin_center, cone->axis);
	const float		dot_ray_and_axis_cone = dot(ray->dir, cone->axis);
	float			one_sqr_tan_halfangle_of_cone = tan(cone->angle * M_PI_360);

	one_sqr_tan_halfangle_of_cone *= one_sqr_tan_halfangle_of_cone;
	one_sqr_tan_halfangle_of_cone += 1;
	///1 + квадрат тангенса полугла вершины конуса,
	/// угол в градусах, преобразуем в радианы для tan()

	float 			a, b, c, discriminant;

	a = dot(ray->dir, ray->dir) - dot_ray_and_axis_cone * dot_ray_and_axis_cone
			* one_sqr_tan_halfangle_of_cone;
	b = 2 * (dot(origin_center, ray->dir) - dot_ray_and_axis_cone
			* dot_origin_center_and_axis_cone * one_sqr_tan_halfangle_of_cone);
	c = dot(origin_center, origin_center) - dot_origin_center_and_axis_cone
			* dot_origin_center_and_axis_cone * one_sqr_tan_halfangle_of_cone;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return false;

	float root = (-b - sqrt(discriminant)) / (2 * a);
	float root2 = (-b + sqrt(discriminant)) / (2 * a);
	if (root < 0 || (root > root2 && root2 > 0)) /// пересечение перед камерой,
		root = root2;							/// берем меньший (ближайший)
	if (root < best_hit->distance && root > RAY_MIN_EPSILON && root > 0)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		const float3 cone_forming = fast_normalize(best_hit->pos - cone->center);
					/// вектор прямой направляющей конуса на которой лежит pos
		best_hit->normal = fast_normalize(dot(cone->axis, cone_forming) > 0 ?
				cone_forming - cone->axis : cone->axis - cone_forming);
		return true;
	}
	return false;
}


bool				ray_cylinder_intersect(
		t_ray *ray,
		__global const t_object *cylinder,
		t_rayhit *best_hit)
{
	const float3	origin_center = ray->origin - cylinder->center;
	const float		dot_origin_center_and_axis_cylinder = dot(origin_center,
						cylinder->axis);
	const float		dot_ray_and_axis_cylinder = dot(ray->dir, cylinder->axis);

	float 			a, b, c, discriminant;

	a = dot(ray->dir, ray->dir) - dot_ray_and_axis_cylinder
			* dot_ray_and_axis_cylinder;
	b = 2 * (dot(origin_center, ray->dir) - dot_ray_and_axis_cylinder
			* dot_origin_center_and_axis_cylinder);
	c = dot(origin_center, origin_center) - dot_origin_center_and_axis_cylinder
			* dot_origin_center_and_axis_cylinder
			- cylinder->radius * cylinder->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	return false;

	float root = (-b - sqrt(discriminant)) / (2 * a);
	float root2 = (-b + sqrt(discriminant)) / (2 * a);
	if (root < 0 || (root > root2 && root2 > 0)) /// пересечение перед камерой,
		root = root2;							/// берем меньший (ближайший)
	if (root < best_hit->distance && root > RAY_MIN_EPSILON && root > 0)
	{
		best_hit->distance = root;
		best_hit->pos = ray->origin + root * ray->dir;
		best_hit->normal = fast_normalize(orthogonalization(
				best_hit->pos - cylinder->center, cylinder->axis));
		///ортогонализация для R2 (процесс Грама-Шмидта)
		//todo вынести функцию отдельно в утилиты
 		return true;
	}
	return false;
}

