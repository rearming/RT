
bool				ray_triangle_intersect_MT(
		t_ray *ray,
		__global const t_object *triangle,
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
		best_hit->normal = fast_normalize(cross(v0v1, v0v2));
		best_hit->pos = ray->origin + ray->dir * intersect_dist;
		return true;
	}
	return false;
}
bool				ray_triangle_intersect_MT_polygon(
		float3 v0, float3 v1, float3 v2,
		float3 vn,
		float3 vt0, float3 vt1, float3 vt2,
		t_ray *ray,
		t_rayhit *best_hit)
{
	const float3	v0v1 = v1 - v0;
	const float3	v0v2 = v2 - v0;

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
	float3	tvec = ray->origin - v0;
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
		best_hit->normal = vn;
		best_hit->pos = ray->origin + ray->dir * intersect_dist;
		return true;
	}
	return false;
}

