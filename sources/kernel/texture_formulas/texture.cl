int		convert_x(t_rayhit *hit,
				  __global const t_texture_info *texture_info,
				  __global const t_object *object)
{
	float	u;
	int		x;

	u = atan2(hit->normal.x, hit->normal.z) + object->material.texture_position.x;
	if (u < 0)
	u += 2 * M_PI_F;
	u *= M_1_PI_F / 2;
	x = (int) ((texture_info->width - 1) * u);
	x = check_borders(x, texture_info->width - 1, 1);
	return (x);
}

int		convert_y(t_rayhit *hit,
				__global const t_texture_info *texture_info,
				__global const t_object *object)
{
	float	v;
	int		y;
	float3	help;

	if (object->type == SPHERE)
	{
		v = 0.5 - asin(hit->normal.y) * M_1_PI_F;
		y = (int) (v * (texture_info->height - 1));
		y = check_borders(y, texture_info->height - 1, 1);
	}
	else
	{
		if (object->type == CONE)
			v = length(object->center - hit->pos) * cos(atan(object->angle));
		help = (object->type == CONE) ? hit->normal * v :
					hit->normal * -object->radius;
		v = length(help + hit->pos - object->center);
		y = (int)(v * texture_info->width / texture_info->height * 100);
		y = check_borders(y, texture_info->height - 1, 2);
	}
	return (y);
}

int		texture_to_plane(t_rayhit *hit,
						__global const t_texture_info *texture_info,
						__global const int *texture_list,
						__global const t_object *object)
{
	float3	buf_u;
	float3	buf_v;
	int		x;
	int		y;
	int 	scale;

	scale = (object->center.z == 0) ? 1 : 4 * object->center.z;
	buf_u = cross(hit->normal, (float3){0.f, 1.0f, 0.f});
	if (fabs(length(buf_u)) < 0.0001f)
		buf_u = cross(hit->normal, (float3) {0.f, 0.0f, 1.0f});
	buf_v = cross(hit->normal, buf_u);
	x = (int)(texture_info->width * (dot(buf_u, hit->pos) + object->center.x + object->material.texture_position.x)
			/ scale) % texture_info->width;
	y = (int)(texture_info->height * (dot(buf_v, hit->pos) + object->center.y + object->material.texture_position.y)
			/ scale) % texture_info->height;
	if (x < 0)
		x += texture_info->width;
	if (y < 0)
		y += texture_info->height;
	return (x + y * texture_info->width + texture_info->start);
}

float3	texture(t_ray *out_ray,
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

	if (object->type == SPHERE || object->type == CONE || object->type == CYLINDER)
	{
		x = convert_x(hit, texture_info, object);
		y = convert_y(hit, texture_info, object);
		coord = x + y * texture_info->width + texture_info->start;
	}
	else if (object->type == PLANE)
		coord = texture_to_plane(hit, texture_info, texture_list, object);
	color = get_float3_color(texture_list[coord]);
	return (color);
}
