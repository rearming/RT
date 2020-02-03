/*static int		check_borders(int a, int max, int type)
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

static int		convert_x(
 		float3 normal,
 		t_texture_info texture_info)
{
	double	u;
	int		x;

	u = atan2f(normal.x, normal.z);
	if (u < 0)
		u += 2 * M_PI;
	u *= M_1_PI / 2;
	x = (int)((texture_info.width - 1) * u);
	x = check_borders(x, texture_info.width- 1, 1);
	return (x);
}

static int		convert_y(
 			float3 normal,
 			float3 point,
 			t_object  *obj,
 			t_texture_info texture_info)
{
	double	v;
	int		y;
	float3	help;

	if (obj->type == SPHERE)
	{
		v = 0.5 - asinf(normal.y) * M_1_PI;
		y = (int)(v * (texture_info.height - 1));
		y = check_borders(y, texture_info.height - 1, 1);
	}
	else
	{
		if (obj->type == CONE)
		{
			v = length(obj->center - point));
			v *= cosf(atanf(obj->angle));
		}
		help = (obj->type == CONE) ? normal * v : normal * -obj->len;
		v = length(help + point - obj->normal);
		y = (int)(v * texture_info.width / texture_info.height * 100);
		y = check_borders(y, texture_info.height - 1, 2);
	}
	return (y);
}

static int2		texture_on_plane(float3 normal, float3 point, float3 pos,  t_texture_info texture_info)
{
	int2	dot;
	float3	buf_u;
	float3	buf_v;

	buf_u = cross(normal, (float3){0.f, 1.f, 0.f});
	if (fabsf(lenght(buf_u)) < 0.0001f)
		buf_u = cross(normal, (t_vec){0.f, 0.f, 1.f});
	buf_v = cross(normal, buf_u);
	dot.x = (int)(texture_info.width * (dot(buf_u, point) + pos.x) / (4 * pos.z)) % texture_info.width;
	dot.y = (int)(texture_info.height * (dot(buf_v, point) + pos.y) / (4 * pos.z)) % texture_info.height;
	if (dot.x < 0)
		dot.x += texture_info.width;
	if (dot.y < 0)
		dot.y += texture_info.height;
	return (dot);
}

t_color			texture(float3 normal, float *texture, t_object *obj, float3 dot_on_object)
{
	t_color		col;
	Uint32		color;
	int2		dot_on_texture;

	SDL_LockSurface(texture);
	if (obj->type == PLANE)
		dot_on_texture = t_plane(normal, dot_on_object, obj->material.texture_position, texture);
	else
	{
		dot_on_texture.x = convert_x(normal, texture);
		dot_on_texture.y = convert_y(normal, dot_on_object, obj, texture);
	}
	color = *((Uint32*)((Uint8*)texture->pixels + ((Uint32)dot_on_texture.y *
					(Uint32)texture->pitch) + ((Uint32)dot_on_texture.x * texture->format->BytesPerPixel)));
	SDL_GetRGB(color, texture->format, (Uint8 *)&col.r, (Uint8 *)&col.g,
			   (Uint8 *)&col.b);
	SDL_UnlockSurface(texture);
	return (col);
}*/