
void 	change_format(int i_color, float3 *f_color)
{
	f_color->x = (i_color >> 16) & 0xFF;
	f_color->y = (i_color >> 8) & 0xFF;
	f_color->z = i_color & 0xFF;
	f_color->x *= 0.00392156862f; // 1/255
	f_color->y *= 0.00392156862f;// 1/255
	f_color->z *= 0.00392156862f;// 1/255
}

float3 texture(t_ray *out_ray,
			   t_rayhit *hit,
			   __global const t_texture_info *texture_info,
			   __global const float *texture_list,
			   __global const t_object *object)
{
	float	u;
	float	v;
	int		x;
	int		y;
	int		coord;
	float3	color;

	u = atan2(hit->normal.x, hit->normal.z) + object->material.texture_position.x;
	if (u < 0.0f)
		u += 2.0f * M_PI_F;
	u *= M_1_PI_F / 2.0f;
	x = (int)((texture_info->width - 1.0f) * u);
	x = check_borders(x, texture_info->width - 1.0f, 1.0f);
	v = 0.5f - asin(hit->normal.y) * M_1_PI_F + object->material.texture_position.y;
	y = (int)(v * (texture_info->height - 1.0f));
	y = check_borders(y, texture_info->height - 1.0f, 1.0f);
	coord = x + y * texture_info->width + texture_info->start;
	change_format((int)texture_list[coord], &color);
	return (color);
}
