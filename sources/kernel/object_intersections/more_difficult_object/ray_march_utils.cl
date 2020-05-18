int			ray_march_simple_obj(t_ray *ray,
		__global const t_object *objects,
		t_rayhit *out_best_hit,
		int i)
{
	t_rayhit c = *out_best_hit;
	if(ray_march(ray, &objects[i], &c))
	{
		*out_best_hit = c;
		return i;
	}
	t_ray r_plus = (t_ray){.origin = ray->origin
			+ RAY_MARCH_MAX_DIST * ray->dir,
			.dir = -ray->dir, .energy = ray->energy};
	t_ray r_minus = (t_ray){.origin = ray->origin
			- RAY_MARCH_MAX_DIST * ray->dir,
			.dir = -ray->dir, .energy = ray->energy};
	t_rayhit p = (t_rayhit){.distance = RAY_MARCH_MAX_DIST, .pos = ray->origin,
						 .normal = -ray->dir};
	t_rayhit m = (t_rayhit){.distance = RAY_MARCH_MAX_DIST, .pos = ray->origin,
						 .normal = r_plus.dir};
	if (!(ray_march(&r_plus, &objects[i], &p)
			&& ray_march(&r_minus, &objects[i], &m)))
		return -1;
	out_best_hit->distance = RAY_MIN_EPSILON;
	out_best_hit->pos = ray->origin;
	out_best_hit->normal = -ray->dir;
	return i;
}


int			ray_march_inter_s_obj(t_ray *ray,
			__global const t_object *objects,
			t_rayhit *out_best_hit,
			int i)
{
	t_rayhit	a = *out_best_hit;
	t_rayhit	b = *out_best_hit;
	if (ray_march(ray, &objects[objects[i].complicated_index], &b)
			&& ray_march(ray, &objects[i], &a))
	{
		float max_dist = (a.distance > b.distance ? a.distance : b.distance);
		t_ray		r = (t_ray){.origin = ray->origin + max_dist * ray->dir,
				.dir = -ray->dir, .energy = ray->energy};
		t_rayhit	c = (t_rayhit){.distance = max_dist, .pos = ray->origin,
				.normal = ray->dir};
		if (!ray_march(&r, a.distance < b.distance ?  &objects[i]
				: &objects[objects[i].complicated_index], &c))
		{
			*out_best_hit = a.distance > b.distance ? a : b;
			return a.distance > b.distance ? i : objects[i].complicated_index;
		}
	}
	return -1;
}

int			ray_march_diff_obj(t_ray *ray,
			__global const t_object *objects,
			t_rayhit *out_best_hit,
			int i)
{
	int a, b;
	if (objects[i].complicated_index < 0)
		return -1;
	else
	{
		b = i;
		a = objects[i].complicated_index;
	}
	t_rayhit	a_h = *out_best_hit;
	bool		a_hit = ray_march(ray, &objects[a], &a_h);
	if (!a_hit)
		return -1;
	t_rayhit	b_h = *out_best_hit;
	bool		b_hit = ray_march(ray, &objects[b], &b_h);
	if ((a_hit && !b_hit) || (a_h.distance < b_h.distance))
	{
		*out_best_hit = a_h;
		return a;
	}
	t_ray		r = *ray;
	r.origin = a_h.pos;
	r.dir = -r.dir;
	if (ray_march(&r, &objects[b], &b_h))
	{
		*out_best_hit = a_h;
		return a;
	}
	r.origin = ray->origin + (RAY_MARCH_MAX_DIST) * ray->dir;
	a_h.distance = RAY_MARCH_MAX_DIST;
	a_h.pos = ray->origin;
	b_h.distance = RAY_MARCH_MAX_DIST;
	b_h.pos = ray->origin;
	ray_march(&r, &objects[a], &a_h);
	ray_march(&r, &objects[b], &b_h);
	if (a_h.distance > b_h.distance)
		return -1;
	a_h.distance = length(a_h.pos - ray->origin);
	a_h.normal = -a_h.normal;
	*out_best_hit = a_h;
	return b;
}