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

static int		convert_x(float3 normal,  float *texture)
{
	double	u;
	int		x;

	u = atan2f(normal.x, normal.z);
	if (u < 0)
		u += 2 * M_PI;
	u *= M_1_PI / 2;
	x = (int)((texture->w - 1) * u);
	x = check_borders(x, texture->w - 1, 1);
	return (x);
}

static int		convert_y(float3 normal, float3 point,t_object  *obj, float *texture)
{
	double	v;
	int		y;
	float3	help;

	if (obj->type == SPHERE)
	{
		v = 0.5 - asinf(normal.y) * M_1_PI;
		y = (int)(v * (texture->h - 1));
		y = check_borders(y, texture->h - 1, 1);
	}
	else
	{
		if (obj->type == CONE)
		{
			v = vec_magnitude(vec_subtract(obj->center, point));
			v *= cosf(atanf(obj->angle));
		}
		help = (obj->type == CONE) ? vec_mult_by_scalar(normal, v) :
			   vec_mult_by_scalar(normal, -obj->len);
		v = vec_magnitude(vec_subtract(vec_add(help, point), obj->normal));
		y = (int)(v * texture->w / texture->h * 100);
		y = check_borders(y, texture->h - 1, 2);
	}
	return (y);
}

static int2		texture_on_plane(float3 normal, float3 point, float3 pos,  float *texture)
{
	int2	dot;
	float3	buf_u;
	float3	buf_v;

	buf_u = cross(normal, (float3){0.f, 1.f, 0.f});
	if (fabsf(vec_magnitude(buf_u)) < 0.0001f)
		buf_u = cross(normal, (t_vec){0.f, 0.f, 1.f});
	buf_v = cross(normal, buf_u);
	dot.x = (int)(texture->w * (dot_product(buf_u, point) + pos.x) / (4 * pos.z)) % tex->w;
	dot.y = (int)(texture->h * (dot_product(buf_v, point) + pos.y) / (4 * pos.z)) % tex->h;
	if (dot.x < 0)
		dot.x += texture->w;
	if (dot.y < 0)
		dot.y += texture->h;
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