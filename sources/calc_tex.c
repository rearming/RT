/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:11:06 by gfoote            #+#    #+#             */
/*   Updated: 2019/12/18 17:11:07 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		x_coord(t_vec normal, SDL_Surface *texture)
{
	double	v;
	int		x;

	v = atan2f(normal.x, normal.z);
	if (v < 0)
		v += 2 * M_PI;
	v *= M_1_PI / 2;
	x = (int)((texture->w - 1) * v);
	if (x < 0 || x > texture->w - 1)
		x = (x < 0) ? 0 : texture->w - 1;
	return (x);
}

static int		y_coord(t_vec normal, t_obj *obj, SDL_Surface *tex, t_vec point)
{
	double	u;
	int		y;
	t_vec	help;

	if (obj->name == SPHERE)
	{
		u = 0.5 - asinf(normal.y) * M_1_PI;
		y = (int)(u * (tex->h - 1));
		if (y < 0 || y > (tex->h - 1))
			y = (y < 0) ? 0 : tex->h - 1;
	}
	else
	{
		if (obj->name == CONE)
		{
			u = length_v(sub_v(obj->pos, point));
			u *= cosf(atanf(obj->size));
		}
		help = (obj->name == CONE) ? v_multiply_l(normal, u) :
				v_multiply_l(normal, -obj->size);
		u = length_v(sub_v(add_v(help, point), obj->pos));
		y = (int)(u * tex->w / tex->h * 100);
		y = (y > (tex->h - 1)) ? y % (tex->h - 1) : y;
	}
	return (y);
}

static t_pos	t_plane(t_vec normal, SDL_Surface *tex, t_vec point, t_vec pos)
{
	int		x;
	int		y;
	t_vec	buf_u;
	t_vec	buf_v;

	buf_u = cross(normal, (t_vec){0.f, 1.f, 0.f});
	if (fabsf(length_v(buf_u)) < 0.0001f)
		buf_u = cross(normal, (t_vec){0.f, 0.f, 1.f});
	buf_v = cross(normal, buf_u);
	x = (int)(tex->w * (dot(buf_u, point) + pos.x) / (4 * pos.z)) % tex->w;
	y = (int)(tex->h * (dot(buf_v, point) + pos.y) / (4 * pos.z)) % tex->h;
	if (x < 0)
		x += tex->w;
	if (y < 0)
		y += tex->h;
	return ((t_pos){x, y});
}

t_color			texture(t_ray ray_nv, SDL_Surface *tex, t_obj *obj, t_vec point_n, t_vec pos) //add pos of texture to object parametrs
{
	t_color		col;
	Uint32		color;
	t_pos		point;

	SDL_LockSurface(tex);
	if (obj->name == PLANE)
		point = t_plane(ray_nv.origin, tex, point_n, pos);
	else
	{
		point.st = x_coord(ray_nv.origin, tex);
		point.fin = y_coord(ray_nv.origin, obj, tex, point_n);
	}
	color = *((Uint32*)((Uint8*)tex->pixels + ((Uint32)point.fin *
	(Uint32)tex->pitch) + ((Uint32)point.st * tex->format->BytesPerPixel)));
	SDL_GetRGB(color, tex->format, (Uint8 *)&col.r, (Uint8 *)&col.g,
		(Uint8 *)&col.b);
	SDL_UnlockSurface(tex);
	return (col);
}
