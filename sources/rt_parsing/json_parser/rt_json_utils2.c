/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_json_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
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

int			check_tmp(bool *checker, int type)
{
	int check;
	int count;

	check = checker[CENTER];
	check += (type == PLANE) ? checker[NORMAL] : 0;
	check += (type == ROUND_CONE) ? checker[ROUND_CONE] : 0;
	check += (type == TORUS_CAPPED || type == CONE) ? checker[ANGLE] : 0;
	check += (type == BOX || type == ELLIPSOID_RAYMARCH) ? checker[SIZE] : 0;
	check += (type == TORUS_CAPPED || type == TORUS) ? checker[RADIUS_RING] : 0;
	check += (type == SPHERE || type == CYLINDER || type == TORUS || type > 12
		|| type == CAPSULE || type == ELLIPSOID) ? checker[RADIUS] : 0;
	check += (type == CONE || type == CYLINDER || type == CAPSULE
		|| type == ROUND_CONE) ? checker[AXIS] : 0;
	check += (type == PARABOLOID || type == ELLIPSOID || type == CAPSULE ||
		type == HEX_PRISM || type == ROUND_CONE) ? checker[DISTANCE] : 0;
	count = 2;
	count += (type == ROUND_CONE) ? 3 : 0;
	count += (type == CONE || type == CYLINDER || type == TORUS
		|| type == ELLIPSOID || type == HEX_PRISM) ? 1 : 0;
	count += (type == CAPSULE || type == TORUS_CAPPED) ? 2 : 0;
	if (check - count != 0)
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS,
			object_name(type)));
	return (check);
}

static int	sum_check(bool *checker, int type)
{
	int i;
	int checker_sum;

	checker_sum = checker[CENTER] + checker[NORMAL]
			+ checker[VMIN] + checker[VMAX]
			+ checker[RADIUS] + checker[ANGLE]
			+ checker[DISTANCE] + checker[SIZE]
			+ checker[RADIUS_RING] + checker[RADIUS_2];
	if (type == 0)
	{
		i = -1;
		checker_sum = 0;
		while (++i < (45))
			checker_sum += checker[i];
	}
	else if (type == 1)
		checker_sum += checker[ALFA_ANGLE] + checker[BETA_ANGLE]
				+ checker[GAMMA_ANGLE] + checker[RAYMARCH]
				+ checker[RAYMARCH_INDEX];
	else
		checker_sum += checker[LEN] + checker[AXIS];
	return (checker_sum);
}

void		check_object(bool *checker, int type, bool texture_pbr)
{
	int check;

	if (type != TEST_OBJECT && type != AABB && type != TRIANGLE)
	{
		check = sum_check(checker, 1);
		check += (type == PLANE) ? checker[LEN] + checker[AXIS] : 0;
		check += (type == CONE || type == CYLINDER) ? checker[AXIS] : 0;
		if (type > ELLIPSOID)
			check = sum_check(checker, 2);
		if ((check - check_tmp(checker, type)) != 0 || check == 0)
			rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS,
					object_name(type)));
	}
	if (checker[EMISSION_COLOR] + checker[EMISSION_POWER] == 1)
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS,
				object_name(type)));
	if (checker[TEXTURE] && type > CONE)
		rt_raise_error(ERR_INVALID_TEXTURE_OBJECT);
	if (texture_pbr == true && (checker[TEXTURE] +
		checker[TEXTURE_NORMAL] + checker[TEXTURE_PBR_INDEX] != 3 ||
		type > CONE))
		rt_raise_error(ERR_IVALID_BUMP_INITIALIZATION);
}

void		check_camera_or_light(bool *checker, int type, int structure_type)
{
	int check_here;
	int check;

	check = sum_check(checker, 0);
	check_here = checker[POS] + checker[ROTATION];
	if (structure_type == CAMERA &&
		(check - check_here != 0 || check_here != 2))
		rt_raise_error(ERR_PARSING_WRONG_CAMERA_PARAMS);
	if (structure_type == LIGHT)
	{
		check_here = (checker[INTENSITY] + checker[COLOR]);
		check_here += (type == DIRECTIONAL) ? checker[DIRECTION] : 0;
		check_here += (type == POINT) ? checker[POS] : 0;
		if (check - check_here != 0 ||
			(type == AMBIENT && check_here != 2)
			|| (check_here != 3 && (type == DIRECTIONAL
			|| type == POINT)))
			rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
	}
}
