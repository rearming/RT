int		check_borders(int a, int max, int type)
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

	u = atan2(normal.x, normal.z);
	if (u < 0)
		u += 2 * M_PI;
	u *= M_1_PI / 2;
	x = (int)((texture_info.width - 1) * u);
	x = check_borders(x, texture_info.width - 1, 1);
	v = 0.5 - asin(normal.y) * M_1_PI;
	y = (int)(v * (texture_info.height - 1));
	y = check_borders(y, texture_info.height - 1, 1);
	printf("%f\n", texture[x + y * texture_info.width + texture_info.start]); //текстура не передается сюда?
	return ((int)(texture[x + y * texture_info.width + texture_info.start]));
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
	scale = (sqrt(discriminant) / (2.0 * a));
	return (scale);

}

float3		skybox_normal(t_ray ray)
{
	float3 normal;
	float3 point = (float3)(0.0);

	point = ray.origin + ray.dir * scale(ray, 10); //scale_between(sphere(r=10)));//find hit object to sphere
	//printf("scale = %f\n", scale(ray, 10));
	normal = normalize(point - ray.origin); //camera_pos = ray.origin
	return (normal);
}