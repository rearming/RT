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

int		rt_skybox(__constant float *texture, t_texture_info texture_info, float3 normal)
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
	return ((int)(texture[x + y * texture_info.width]));
}