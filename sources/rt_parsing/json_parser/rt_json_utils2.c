/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_json_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:48:00 by gfoote            #+#    #+#             */
/*   Updated: 2020/03/10 16:48:02 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_parsing.h"

char		*object_name(int type)
{
	if (type == SPHERE)
		return ("Sphere");
	if (type == CONE)
		return ("Cone");
	if (type == CYLINDER)
		return ("Cylinder");
	if (type == PLANE)
		return ("Plane");
	if (type == ELLIPSOID_RAYMARCH)
		return ("ellipsoid raymarch");
	if (type == AABB)
		return ("AABB");
	if (type == TRIANGLE)
		return ("Triangle");
	if (type == PARABOLOID)
		return ("Paraboloid");
	if (type == ELLIPSOID || type == BOX)
		return (type == BOX) ? ("box") : ("Ellipsoid");
	if (type == CAPSULE || type == TORUS)
		return (type == TORUS) ? ("torus") : ("capsule");
	if (type == TORUS_CAPPED || type == HEX_PRISM)
		return (type == HEX_PRISM) ? ("hex prism") : ("torus capped");
	if (type == ROUND_CONE || type == TEST_OBJECT)
		return (type == TEST_OBJECT) ? ("test object") : ("round cone");
	return (NULL);
}

int			check_tmp(t_tmp *tmp)
{
	int check;

	check = tmp->checker[CENTER];
	if (tmp->type == SPHERE)
		check += tmp->checker[RADIUS];
	if (tmp->type == CYLINDER || tmp->type == CAPSULE)
		check += tmp->checker[RADIUS] + tmp->checker[AXIS];
	if (tmp->type == CONE)
		check += tmp->checker[ANGLE] + tmp->checker[AXIS];
	if (tmp->type == PLANE)
		check += tmp->checker[NORMAL];
	if (tmp->type == PARABOLOID || tmp->type == CAPSULE)
		check += tmp->checker[DISTANCE];
	if (tmp->type == BOX || tmp->type == ELLIPSOID_RAYMARCH)
		check += tmp->checker[SIZE];
	if (tmp->type == TORUS || tmp->type == TORUS_CAPPED)
		check += tmp->checker[RADIUS] + tmp->checker[RADIUS_RING];
	if (tmp->type == TORUS_CAPPED)
		check += tmp->checker[ANGLE];
	if (tmp->type == HEX_PRISM || tmp->type == ELLIPSOID)
		check += tmp->checker[RADIUS] + tmp->checker[DISTANCE];
	if (tmp->type == ROUND_CONE)
		check += tmp->checker[AXIS] + tmp->checker[RADIUS]
				+ tmp->checker[DISTANCE] + tmp->checker[RADIUS_2];
	return (check);
}

static int	sum_check(t_tmp *tmp)
{
	return (tmp->checker[CENTER] + tmp->checker[NORMAL]
			+ tmp->checker[VMIN] + tmp->checker[VMAX]
			+ tmp->checker[RADIUS] + tmp->checker[ANGLE]
			+ tmp->checker[DISTANCE] + tmp->checker[SIZE]
			+ tmp->checker[RADIUS_RING] + tmp->checker[RADIUS_2]
			+ tmp->checker[ALFA_ANGLE] + tmp->checker[COMPLICATED]);
}

void		check_object(t_tmp *tmp)
{
	int check;

	if (tmp->type != TEST_OBJECT && tmp->type != AABB && tmp->type != TRIANGLE)
	{
		check = sum_check(tmp);
		if (tmp->type == PLANE)
			check += tmp->checker[LEN] + tmp->checker[AXIS];
		else if (tmp->type == CONE || tmp->type == CYLINDER)
			check += tmp->checker[AXIS];
		else if (tmp->type > ELLIPSOID)
			check += tmp->checker[LEN] + tmp->checker[AXIS]
					- tmp->checker[ALFA_ANGLE] - tmp->checker[COMPLICATED];
		if ((check - check_tmp(tmp)) != 0 && check > 0)
			rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS,
					object_name(tmp->type)));
	}
	if (tmp->checker[EMISSION_COLOR] + tmp->checker[EMISSION_POWER] == 1)
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS,
				object_name(tmp->type)));
	if (tmp->checker[TEXTURE] && !(tmp->type == SPHERE || tmp->type == CONE
		|| tmp->type == CYLINDER || tmp->type == PLANE))
		rt_raise_error(ERR_INVALID_TEXTURE_OBJECT);
	if (tmp->texture_pbr == true && (tmp->checker[TEXTURE] +
	tmp->checker[TEXTURE_NORMAL] + tmp->checker[TEXTURE_PBR_INDEX] != 3))
		rt_raise_error(ERR_IVALID_BUMP_INITIALIZATION);
}

void		check_camera_or_light(t_tmp *tmp)
{
	int check_count;
	int check;

	check = 0;
	check_count = 0;
	while (check_count++ < 43)
		check += tmp->checker[check_count];
	if (tmp->struct_type == CAMERA &&
	(check - tmp->checker[POS] - tmp->checker[ROTATION] != 0 ||
	tmp->checker[POS] + tmp->checker[ROTATION] != 2))
		rt_raise_error(ERR_PARSING_WRONG_CAMERA_PARAMS);
	if (tmp->struct_type == LIGHT)
	{
		check_count = (tmp->checker[INTENSITY] + tmp->checker[COLOR]);
		if (tmp->type == DIRECTIONAL)
			check_count += tmp->checker[DIRECTION];
		if (tmp->type == POINT)
			check_count += tmp->checker[POS];
		if (check - check_count != 0 ||
			(tmp->type == AMBIENT && check_count != 2)
			|| (check_count != 3 && (tmp->type == DIRECTIONAL
			|| tmp->type == POINT)))
			rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
	}
}
