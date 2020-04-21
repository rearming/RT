bool			ray_march(
		t_ray *ray,
		__global const t_object *obj,
		t_rayhit *best_hit)
{
	/// как сделать матрицу поворота
//	const float a = obj->len;//это углы эйлера альфа, бета, гамма
//	const float b = obj->len;
//	const float g = obj->len;

//	// для удобства сформируем вектор с косинусами, синусами
//	// и минус синусами углов (cos(-x) == cos(x))
//	const float3 c = {cos(a), cos(b), cos(g)};
//	const float3 s = {sin(a), sin(b), sin(g)};
//	const float3 c1 = c;
//	const float3 s1 = -s;
//
//	//матрица поворота в положительном напралении
//	float3	m1 = {c.x * c.z-s.x * c.y * s.z,
//					-c.x * s.z - s.x * c.y * c.z,
//					s.x * s.y};
//	float3	m2 = {s.x * c.z + c.x * c.y * s.z,
//					-s.x * s.z + c.x * c.y * c.z,
//					-c.x * s.y};
//	float3	m3 = {s.y * s.z,
//					s.y * c.z,
//					c.y};
//
//	//матрица поворота в отрицательном напралении
//	float3	l1 = {c1.x * c1.z-s1.x * c1.y * s1.z,
//					-c1.x * s1.z - s1.x * c1.y * c1.z,
//					s1.x * s1.y};
//	float3	l2 = {s1.x * c1.z + c1.x * c1.y * s1.z,
//					-s1.x * s1.z + c1.x * c1.y * c1.z,
//					-c1.x * s1.y};
//	float3	l3 = {s1.y * s1.z,
//					s1.y * c1.z,
//					c1.y};
//
	if (ray_march_hit(ray, obj, best_hit)) /// если есть пересечение считаем нормаль
	{
		/// нахождение нормали, [ex, ey, ez]  смещение относительно точки по осям
		const float3	ex = {RAY_MARCH_SURFACE_ACC, 0, 0};
		const float3	ey = {0, RAY_MARCH_SURFACE_ACC, 0};
		const float3	ez = {0, 0, RAY_MARCH_SURFACE_ACC};
		const float		dist = distan(surface_point, obj);
		/// вектор р - вектор направление градиента близости к поверхности
		const float3	r = {dist - distan(surface_point - ex, obj),
								dist - distan(surface_point - ey, obj),
								dist - distan(surface_point - ez, obj)};

		/// поворачиваем вектор нормали в обратную сторону
		/// obj->rot_n1, 2, 3 - строчки матрицы поворота для углов эйлера
		/// с противоположным знаком  (rotation negative)
		(best_hit->normal).x = dot(obj->rot_n1, r);
		(best_hit->normal).y = dot(obj->rot_n2, r);
		(best_hit->normal).z = dot(obj->rot_n3, r);
		best_hit->normal = fast_normalize(best_hit->normal);
		return true;
	}
	return false;
}

float	distan(float3 surface_point, t_object *obj)
{
	switch (obj->type)
	{
	case (BOX)
		return dist_box(surface_point, obj);
	case (CAPSULE)
		return dist_capsule(surface_point, obj);
	case (TORUS)
		return dist_torus(surface_point, obj);
	case (ELLIPSOID_RAYMARCH)
		return dist_ellipsoid(surface_point, obj);
	case (TORUS_CAPPED)
		return dist_torus_capped(surface_point, obj);
	case (HEX_PRISM)
		return dist_hex_prism(surface_point, obj);
	case (ROUND_CONE)
		return dist_round_cone(surface_point, obj);
	}
}

bool		ray_march_hit(t_ray *ray,
		__global const * t_object *obj,
		t_rayhit *best_hit)
{
	/// для нахождения расстояния сначала повернем и сместим луч,
	/// переходя в СК объекта
	float3	surface_point = ray->origin;

	/// перемещаем точку рей оригн в новую,
	/// поворачивая вектор (рей оригн - обжект сентр) на углы эйлера
	/// obj->rot_p1, 2, 3 - строчки матрицы поворота для углов эйлера
	/// alpha, beta, gamma (прецессия, нутация, вращение) (rotation positive)

	float3	p = {dot(obj->rot_p1, surface_point),
					dot(rot_p2, surface_point),
					dot(rot_p3, surface_point)};
	surface_point = p + obj->center;
	p = surface_point; ///  вот отсюда теперь будет исходить луч относительно объекта

	/// поворачиваем сам вектор направления
	float3	d = {dot(obj->rot_p1, ray->dir),
					dot(obj->rot_p2, ray->dir),
					dot(obj->rot_p3, ray->dir)};

	float	distance, distance_diff;
	/// идем по лучу к поверхности
	switch (obj->type)
	{
		case (BOX)
		{
			for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
			{
				distance_diff = dist_box(surface_point, obj);
				distance += distance_diff;
				surface_point = p + d * distance;

				if(distance > RAY_MARCH_MAX_DIST
						|| distance_diff < RAY_MARCH_SURFACE_ACC)
					break;
			}
			break;
		}

		case (CAPSULE)
		{
			for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
			{
				distance_diff = dist_capsule(surface_point, obj);
				distance += distance_diff;
				surface_point = p + d * distance;

				if(distance > RAY_MARCH_MAX_DIST
						|| distance_diff < RAY_MARCH_SURFACE_ACC)
					break;
			}
			break;
		}

		case (TORUS)
		{
			for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
			{
				distance_diff = dist_torus(surface_point, obj);
				distance += distance_diff;
				surface_point = p + d * distance;

				if(distance > RAY_MARCH_MAX_DIST
						|| distance_diff < RAY_MARCH_SURFACE_ACC)
					break;
			}
			break;
		}

		case (ELLIPSOID_RAYMARCH)
		{
			for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
			{
				distance_diff = dist_ellipsoid(surface_point, obj);
				distance += distance_diff;
				surface_point = p + d * distance;

				if(distance > RAY_MARCH_MAX_DIST
						|| distance_diff < RAY_MARCH_SURFACE_ACC)
					break;
			}
			break;
		}

		case (TORUS_CAPPED)
		{
			for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
			{
				distance_diff = dist_torus_capped(surface_point, obj);
				distance += distance_diff;
				surface_point = p + d * distance;

				if(distance > RAY_MARCH_MAX_DIST
						|| distance_diff < RAY_MARCH_SURFACE_ACC)
					break;
			}
			break;
		}

		case (HEX_PRISM)
		{
			for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
			{
				distance_diff = dist_hex_prism(surface_point, obj);
				distance += distance_diff;
				surface_point = p + d * distance;

				if(distance > RAY_MARCH_MAX_DIST
						|| distance_diff < RAY_MARCH_SURFACE_ACC)
					break;
			}
			break;
		}

		case (ROUND_CONE)
		{
			for(int i = 0; i < RAY_MARCH_MAX_STEPS; i++)
			{
				distance_diff = dist_round_cone(surface_point, obj);
				distance += distance_diff;
				surface_point = p + d * distance;

				if(distance > RAY_MARCH_MAX_DIST
						|| distance_diff < RAY_MARCH_SURFACE_ACC)
					break;
			}
			break;
		}
	} //  end of switch

	/// пересечение ближайшее - возвращаем точку
	if (best_hit->distance > distance
			&& distance > RAY_MIN_EPSILON)
	{
		best_hit->distance = distance;
		best_hit->pos = surface_point;
		return true;
	}
}

float	dist_box(float3 surface_point, t_object *obj)
{
	surface_point -= obj->center;
	float3	s;
	s.x = fabs(surface_point.x) - obj->size.x;
	s.x = s.x >= 0 ? s.x : 0;
	s.y = fabs(surface_point.y) - obj->size.y;
	s.y = s.y >= 0 ? s.y : 0;
	s.z = fabs(surface_point.z) - obj->size.z;
	s.z = s.z >= 0 ? s.z : 0;
	return length(s);
}

float	dist_capsule(float3 surface_point,
					  __global const t_object *obj)
{
	const float3	ab = obj->distance * obj->axis;
	const float3	ap = surface_point - obj->center;

	float t = dot(ab, ap) / dot(ab, ab);
	t = min(max(t, 0.f), 1.f);

	const float3 c = obj->center + t * ab;

	return length(surface_point - c) - obj->radius;
}


float	dist_torus(float3 surface_point, t_object *obj)
{
	float3 p1 = surface_point - obj->center;
	float x = sqrt(p1.x * p1.x + p1.z * p1.z) - obj->radius_ring;
	return sqrt(x * x + p1.y * p1.y) - obj->radius;
}

float	dist_ellipsoid(float3 surface_point, t_object *obj)
{
	float3 p = surface_point - obj->center;
	float k0 = length(p / obj->size);
	float k1 = length(p / (obj->size * obj->size));
	return k0 * (k0 - 1.0) / k1;
}

float	dist_torus_capped(float3 surface_point, t_object *obj)
{
	float3 p = surface_point - obj->center;
	p.x = fabs(p.x);
	float k = 0;
	if (obj->angle > - M_PI /2)
		k = (cos(obj->angle) * p.x > sin(obj->angle) * p.z) ?
				p.x * sin(obj->angle) + p.z * cos(obj->angle)
				:sqrt(p.x * p.x + p.z * p.z);
	else
		k = (cos((obj->angle)) * p.x < sin((obj->angle)) * p.z) ?
				p.z * sin((obj->angle)) + p.x * cos((obj->angle))
				:sqrt(p.x * p.x + p.z * p.z);
	return sqrt(dot(p, p) + obj->radius_ring * obj->radius_ring
				- 2.0 * obj->radius_ring * k) - obj->radius;
}

float	dist_hex_prism(float3 surface_point, t_object *obj)
{
	float3			q = fabs(surface_point - obj->center);
	float			pz = q.z;
	const float3	k = {-0.8660254, 0.5, 0.0f};
	const float		kz = 0.57735f;
	q.z = 0.0f;
	q -= 2.0f * fmin(dot(k, q), 0.0f) * k;

	float3	cl = {clamp(q.x, -kz * obj->radius, kz * obj->radius),
					obj->radius, 0.0f};
	cl.x = length(q - cl) * sign(q.y - obj->radius);
	cl.y = pz - obj->high;
	return clamp(cl.x, cl.y, 0.0f) + length(max(cl, 0.0f));
}

float	dist_round_cone(float3 surface_point, t_object *obj)
{
	const float3	p = surface_point - obj->center;
	const float3	b = obj->center + obj->axis * obj->distance;
	const float3	a = obj->center - obj->axis * obj->distance;
	const float		r1 = obj->radius;
	const float		r2 = obj->radius_2;

	const float3	ba = b - a;
	const float		l2 = dot(ba, ba);
	const float		rr = r1 - r2;
	const float		a2 = l2 - rr * rr;
	const float		il2 = 1.0 / l2;

	const float3	pa = p - a;
	const float		y = dot(pa, ba);
	const float		z = y - l2;
	const float		x2 = dot(pa * l2 - ba * y, pa * l2 - ba * y);
	const float		y2 = y * y * l2;
	const float		z2 = z * z * l2;

	const float		k = sign(rr) * rr * rr * x2;
	if (sign(z) * a2 * z2 > k)
		return sqrt(x2 + z2) * il2 - r2;
	if (sign(y) * a2 * y2 < k )
		return sqrt(x2 + y2) * il2 - r1;
	return (sqrt(x2 * a2 * il2) + y * rr) * il2 - r1;
}






