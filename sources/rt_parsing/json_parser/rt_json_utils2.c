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

void	free_tmp(t_tmp *tmp)
{
	t_tmp	*tmp_iterator;

	while (tmp)
	{
		tmp_iterator = tmp->next;
		free(tmp);
		tmp = tmp_iterator;
	}
	free(tmp);
}

void	check_duplicated(bool *checker, int number)
{
	if (checker[number] == true)
		rt_raise_error(ERR_PARSING_DUPLICATED_PARAM);
	else
		checker[number] = true;
}

char	*object_name(int type)
{
	if (type == SPHERE)
		return "Sphere";
	if (type == CONE)
		return "Cone";
	if (type == CYLINDER)
		return "Cylinder";
	if (type == PLANE)
		return "Plane";
	if (type == AABB)
		return "AABB";
	if (type == TRIANGLE)
		return "Triangle";
	if (type == PARABOLOID)
		return "Paraboloid";
	if (type == ELLIPSOID)
		return "Ellipsoid";
	if (type == BOX)
		return "box";
	if (type == CAPSULE)
		return "capsule";
	if (type == TORUS)
		return "torus";
	if (type == ELLIPSOID_RAYMARCH)
		return "ellipsoid raymarch";
	if (type == TORUS_CAPPED)
		return "torus capped";
	if (type == HEX_PRISM)
		return "hex prism";
	if (type == ROUND_CONE)
		return "round cone";
	if (type == TEST_OBJECT)
		return "test object";
	return NULL;
}

int		check_tmp(t_tmp *tmp)
{
		int check;

		check = tmp->checker[CENTER];
		if (tmp->type == SPHERE)
			check += tmp->checker[RADIUS];
		else if (tmp->type == CYLINDER)
			check += tmp->checker[RADIUS] + tmp->checker[AXIS];
		else if (tmp->type == CONE)
			check += tmp->checker[ANGLE] + tmp->checker[AXIS];
		else if (tmp->type == PLANE)
			check += tmp->checker[NORMAL];
		else if (tmp->type == PARABOLOID)
			check += tmp->checker[DISTANCE];
		else if (tmp->type == ELLIPSOID)
			check += tmp->checker[DISTANCE] + tmp->checker[RADIUS];
		else if (tmp->type == BOX)
			check += tmp->checker[SIZE];
		else if (tmp->type == CAPSULE)
			check += tmp->checker[AXIS] + tmp->checker[RADIUS] + tmp->checker[DISTANCE];
		else if (tmp->type == TORUS)
			check += tmp->checker[RADIUS] + tmp->checker[RADIUS_RING];
		else if (tmp->type == ELLIPSOID_RAYMARCH)
			check += tmp->checker[SIZE];
		else if (tmp->type == TORUS_CAPPED)
			check += tmp->checker[RADIUS] + tmp->checker[DISTANCE] + tmp->checker[ANGLE];
		else if (tmp->type == HEX_PRISM)
			check += tmp->checker[RADIUS] + tmp->checker[DISTANCE];
		else if (tmp->type == ROUND_CONE)
			check += tmp->checker[AXIS] + tmp->checker[RADIUS]
					+ tmp->checker[DISTANCE] + tmp->checker[RADIUS_2];
		return check;
}

void	check_object(t_tmp *tmp)
{
	int check;

	if (tmp->type != TEST_OBJECT && tmp->type != AABB && tmp->type != TRIANGLE)
	{
		check = tmp->checker[CENTER] + tmp->checker[NORMAL]
				+ tmp->checker[VMIN] + tmp->checker[VMAX]
				+ tmp->checker[RADIUS] + tmp->checker[ANGLE]
				+ tmp->checker[DISTANCE] + tmp->checker[SIZE]
				+ tmp->checker[RADIUS_RING] + tmp->checker[RADIUS_2]
				+ tmp->checker[ALFA_ANGLE] + tmp->checker[COMPLICATED];
		if (tmp->type == PLANE)
			check += tmp->checker[LEN] + tmp->checker[AXIS];
		else if (tmp->type == CONE || tmp->type == CYLINDER)
			check += tmp->checker[AXIS];
		else if (tmp->type > ELLIPSOID)
			check += tmp->checker[LEN] + tmp->checker[AXIS]
					- tmp->checker[ALFA_ANGLE] - tmp->checker[COMPLICATED];
		check -= check_tmp(tmp);
		if (check != 0)
			rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS, object_name(tmp->type)));
	}
	if (tmp->checker[EMISSION_COLOR] + tmp->checker[EMISSION_POWER] == 1)
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS, object_name(tmp->type)));
	if (tmp->checker[TEXTURE] && !(tmp->type == SPHERE || tmp->type == CONE
		|| tmp->type == CYLINDER || tmp->type == PLANE))
		rt_raise_error(ERR_INVALID_TEXTURE_OBJECT);
}

void	check_camera_or_light(t_tmp *tmp, bool type)
{
	int check_obligate;
	int check;
	int i;
	int count;

	i = 0;
	check = 0;
	count = 2;
	while (++i < 33)
		check +=tmp->checker[i];
	if (type)
		check_obligate = tmp->checker[POS] + tmp->checker[ROTATION];
	else
	{
		if (tmp->type == AMBIENT)
			check_obligate = (tmp->checker[INTENSITY] + tmp->checker[COLOR]);
		else if (tmp->type == DIRECTIONAL && ++count < 4)
			check_obligate = (tmp->checker[INTENSITY] + tmp->checker[COLOR]
					+ tmp->checker[DIRECTION]);
		else if (tmp->type == POINT && ++count < 4)
			check_obligate = (tmp->checker[INTENSITY] + tmp->checker[COLOR]
							  + tmp->checker[POS]);
		else
			check_obligate = 0;
	}
	if (check_obligate / count != 1 || check - check_obligate != 0)
		(type) ? rt_raise_error(ERR_PARSING_WRONG_CAMERA_PARAMS) :
		rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
}
