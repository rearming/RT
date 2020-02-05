float3		skybox_color(
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		float3 normal)
{
	float3	color;
	double	u;
	int		x;
	double	v;
	int		y;
	int		coord;

	u = atan2(normal.x, normal.z);
	if (u < 0)
		u += 2 * M_PI_F;
	u *= M_1_PI_F / 2;
	x = (int)((texture_info->width - 1) * u);
	x = check_borders(x, texture_info->width - 1, 0);
	v = 0.5 - asin(normal.y) * M_1_PI_F;
	y = (int)(v * (texture_info->height - 1));
	y = check_borders(y, texture_info->height - 1, 0);
	coord = x + y * texture_info->width + texture_info->start;
	change_format((int)texture_list[coord], &color);
	return (color);
}

float 		scale(t_ray ray, float skybox_radius)
{
	float	scale;
	float	discriminant;
	float	a;

	a = dot(ray.dir, ray.dir);
	discriminant = 4.0 * a * skybox_radius * skybox_radius;
	if (discriminant < 0.0)
	{
		return (-1.0);
	}
	scale = sqrt(discriminant) / (2.0 * a);
	return (scale);

}

float3		skybox_normal(t_ray ray)
{
	float3 normal;
	float3 point = (float3)(0.0);

	point = ray.origin + ray.dir * scale(ray, 1);
	normal = normalize(point - ray.origin);
	return (normal);
}