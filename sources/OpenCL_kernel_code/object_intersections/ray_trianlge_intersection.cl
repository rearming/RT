bool				ray_triangle_intersect(
		t_ray *ray,
		__constant t_object *triangle,
		t_rayhit *best_hit)
{
	const float3	v0v1 = triangle->vertices[1] - triangle->vertices[0];
	const float3	v0v2 = triangle->vertices[2] - triangle->vertices[0];
	const float3	normal = fast_normalize(cross(v0v1, v0v2));
	/// нормализовать после вычисления площади треугольника

	const float3	origin_pos = ray->origin - triangle->vertices[0];
	const float		ray_dir_dot_normal = dot(ray->dir, normal);
	if (ray_dir_dot_normal == 0) /// луч параллелен треугольнику
		return false;

	const float		intersect_dist = -dot(origin_pos, normal) / ray_dir_dot_normal;
	const float3	hit_pos = ray->origin + intersect_dist * ray->dir;

	if (intersect_dist < best_hit->distance && intersect_dist > RAY_MIN_EPSILON)
	{
		const float3	edge0 = triangle->vertices[1] - triangle->vertices[0];
		const float3	edge1 = triangle->vertices[2] - triangle->vertices[1];
		const float3	edge2 = triangle->vertices[0] - triangle->vertices[2];
		const float3	C0 = hit_pos - triangle->vertices[0];
		const float3	C1 = hit_pos - triangle->vertices[1];
		const float3	C2 = hit_pos - triangle->vertices[2];

		if (dot(normal, cross(edge0, C0)) > 0 &&
			dot(normal, cross(edge1, C1)) > 0 &&
			dot(normal, cross(edge2, C2)) > 0)
		{
			best_hit->distance = intersect_dist;
			best_hit->normal = normal;
			best_hit->pos = hit_pos;
			return true;
		}
	}
	return false;
}

bool				ray_triangle_intersect_MT(
		t_ray *ray,
		__constant t_object *triangle,
		t_rayhit *best_hit)
{
	const float3	v0v1 = triangle->vertices[1] - triangle->vertices[0];
	const float3	v0v2 = triangle->vertices[2] - triangle->vertices[0];

	float3	plane_vec = cross(ray->dir, v0v2);
	float	determinant = dot(v0v1, plane_vec);

#ifdef BACKFACE_CULLING
	if (determinant < RAY_MIN_EPSILON)
		return false;
#else
	if (fabs(determinant) < RAY_MIN_EPSILON)
		return false;
#endif

	float 	inverse_determinant = 1 / determinant;
	float3	tvec = ray->origin - triangle->vertices[0];
	float	u = dot(tvec, plane_vec) * inverse_determinant;
	if (u < 0 || u > 1)
		return false;
	float3	qvec = cross(tvec, v0v1);
	float 	v = dot(ray->dir, qvec) * inverse_determinant;
	if (v < 0 || u + v > 1)
		return false;

	float	intersect_dist = dot(v0v2, qvec) * inverse_determinant;

	if (intersect_dist < best_hit->distance && intersect_dist > RAY_MIN_EPSILON)
	{
		best_hit->distance = intersect_dist;
		best_hit->normal = fast_normalize(cross(v0v1, v0v2)); // todo брать это из объекта
		best_hit->pos = ray->origin + ray->dir * intersect_dist;
		return true;
	}
	return false;
}
