float3		skybox_color(
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		float3 normal)
{
	float3	color;
	float	u;
	int		x;
	float	v;
	int		y;
	int		coord;

	u = atan2(normal.x, normal.z);
	if (u < 0.0f)
		u += 2.0f * M_PI_F;
	u *= M_1_PI_F / 2.0f;
	x = (int)((texture_info->width - 1.0f) * u);
	x = check_borders(x, texture_info->width - 1.0f, 0.0f);
	v = 0.5f - asin(normal.y) * M_1_PI_F;
	y = (int)(v * (texture_info->height - 1.0f));
	y = check_borders(y, texture_info->height - 1.0f, 0.0f);
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
	discriminant = 4.0f * a * skybox_radius * skybox_radius;
	if (discriminant < 0.0f)
	{
		return (-1.0f);
	}
	scale = sqrt(discriminant) / (2.0f * a);
	return (scale);

}

float3		skybox_normal(t_ray ray)
{
	float3 normal;
	float3 point = (float3)(0.0f);

	point = ray.origin + ray.dir * scale(ray, 1);
	normal = normalize(point - ray.origin);
	return (normal);
}