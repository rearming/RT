bool			ray_march_dist_capsule(
		t_ray *ray,
		__global const t_object *obj,
		t_rayhit *best_hit)
{
	float3	surface_point;
	float 	distance;
	float 	distance_diff;
	for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
	{
		surface_point = ray->origin + ray->dir * distance;
		distance_diff = dist_capsule(surface_point, obj);
		distance += distance_diff;
		if(distance > RAY_MARCH_MAX_DIST
				|| distance_diff < RAY_MARCH_SURFACE_ACC)
			break;
	}
	if (best_hit->distance > distance
			&& distance > RAY_MIN_EPSILON)
	{
		best_hit->distance = distance;
		best_hit->pos = surface_point;
		const float3 ex = {RAY_MARCH_SURFACE_ACC, 0, 0};
		const float3 ey = {0, RAY_MARCH_SURFACE_ACC, 0};
		const float3 ez = {0, 0, RAY_MARCH_SURFACE_ACC};
		const float d = dist_capsule(surface_point, obj);
		(best_hit->normal).x = d - dist_capsule(surface_point - ex, obj);
		(best_hit->normal).y = d - dist_capsule(surface_point - ey, obj);
		(best_hit->normal).z = d - dist_capsule(surface_point - ez, obj);
		best_hit->normal = fast_normalize(best_hit->normal);
		return true;
	}
	return false;
}

float dist_capsule(float3 surface_point,
			  __global const t_object *obj)
{
	const float3	ab = obj->distance * obj->axis;
	const float3	ap = surface_point - obj->center;

	float t = dot(ab, ap) / dot(ab, ab);
	t = min(max(t, 0.f), 1.f);

	const float3 c = obj->center + t * ab;

	return length(surface_point-c)-obj->radius;
	return -1;
}

//float dist_box(float3 surface_point, t_object *obj)
//{
//	float3	s;
//	s.x = fabs(surface_point.x) - obj->axis.x; ///TODO rename axis to size, here and down
//	s.x = s.x >= 0 ? s.x : 0;
//	s.y = fabs(surface_point.y) - obj->axis.y;
//	s.y = s.y >= 0 ? s.y : 0;
//	s.z = fabs(surface_point.z) - obj->axis.z;
//	s.z = s.z >= 0 ? s.z : 0;
//	return length(s);
//}

//float	dist_torus(float3 surface_point, t_object *obj)
//{
//	float3 p1 = surface_point - obj->center;
//	float x = sqrt(p1.x * p1.x + p1.z * p1.z) - obj->distance;
//	///TODO rename distance to radius_ring
//	return sqrt(x * x + p1.y * p1.y) - obj->radius;
//}

//float	dist_ellipsoid(float3 surface_point, t_object *obj)
//{
//	float3 p = surface_point - obj->center;
//	float k0 = length(p / obj->axis); ///TODO rename axis to size
//	float k1 = length(p / (obj->axis * obj->axis));
//	return k0 * (k0 - 1.0) / k1;
//}

//float	dist_ellipsoid(float3 surface_point, t_object *obj)
//{
//	float p = surface_point - obj->center;
//	p.x = abs(p.x);
//	float k = (cos(obj->angle) * p.x > sin(obj->angle) * p.y) ?
//			p.x * sin(obj->angle) + p.y * cos(obj->angle)
//			:sqrt(p.x * p.x + p.y * p.y);
//	return sqrt(dot(p, p) + obj->distance * obj->distance - 2.0 * obj->distance * k) - obj->radius;
//}








