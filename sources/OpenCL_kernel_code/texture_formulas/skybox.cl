/*int		check_borders(int a, int max, int type)
{
	if (a < 0)
		return (0);
	if (a > max)
	{
		if (type == 1)
			return (max);
		else
			return (a % max);
	}
	return (a);
}

int		skybox_color(__constant float *texture, t_texture_info texture_info, float3 normal)
{
	double	u;
	int		x;
	double	v;
	int		y;

	u = atan2f(normal.x, normal.z);
	if (u < 0)
		u += 2 * M_PI;
	u *= M_1_PI / 2;
	x = (int)((texture_info.width - 1) * u);
	x = check_borders(x, texture_info.width - 1, 1);
	v = 0.5 - asinf(normal.y) * M_1_PI;
	y = (int)(v * (texture_info.height - 1));
	y = check_borders(y, texture_info.height - 1, 1);
	return ((int)(texture[x + y * texture_info.width + texture_info.size]));
}
*/

float scale(t_ray *ray, float skybox_radius)
{
	float	scale;
	float	discriminant;
	float	a;

	a = dot(ray->dir, ray->dir);
	discriminant = 4.0f * a * skybox_radius * skybox_radius;
	if (discriminant < 0)
	{
		printf("magic\n");
		rt_raise_error(0);
	}
	scale = (sqrtf(discriminant) / (2.0 * a));
	return (scale);

}

void		skybox_normal(
		t_ray *ray,
		float3 *normal)
{
	float3 point = (0);

	printf("here\n");
	point = ray->origin + ray->dir * scale(ray, 10); //scale_between(sphere(r=10)));//find hit object to sphere
	*normal = normalize(point - ray->origin); //camera_pos = ray.origin
}