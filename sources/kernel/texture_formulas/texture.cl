float3 texture(t_ray *out_ray,
			   t_rayhit *hit,
			   __global const t_texture_info *texture_info,
			   __global const int *texture_list,
			   __global const t_object *object)
{
	float	u;
	float	v;
	int		x;
	int		y;
	int		coord;
	float3	color;

	u = atan2(hit->normal.x, hit->normal.z) + object->material.texture_position.x;
	if (u < 0)
		u += 2 * M_PI_F;
	u *= M_1_PI_F / 2;
	x = (int)((texture_info->width - 1) * u);
	x = check_borders(x, texture_info->width - 1, 1);
	v = 0.5 - asin(hit->normal.y) * M_1_PI_F + object->material.texture_position.y;
	y = (int)(v * (texture_info->height - 1));
	y = check_borders(y, texture_info->height - 1, 1);
	coord = x + y * texture_info->width + texture_info->start;
	color = get_float3_color(texture_list[coord]);
	return (color);
}
