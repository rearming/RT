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

void	check_object(t_tmp *tmp)
{
	int check_obligate;
	int check;
	int count;

	count = 2;
	check_obligate = 0;
	check = tmp->checker[NORMAL] + tmp->checker[DISTANCE] + tmp->checker[AXIS]
		+ tmp->checker[ANGLE] + tmp->checker[LEN] + tmp->checker[VMIN] +
		tmp->checker[VMAX] + tmp->checker[CENTER] + tmp->checker[RADIUS] +
		tmp->checker[POS] + tmp->checker[ROTATION] + tmp->checker[INTENSITY]
		+ tmp->checker[DIRECTION] + tmp->checker[COLOR];
	if (tmp->type == SPHERE)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[RADIUS]);
	else if (tmp->type == PLANE)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[NORMAL]);
	else if ((tmp->type == CONE || tmp->type == CYLINDER) && ++count < 4)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[AXIS]
			+ tmp->checker[ANGLE]);
	else if (tmp->type == PARABOLOID && ++count < 4)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[DISTANCE]
			+ tmp->checker[AXIS]);
	else if (tmp->type == ELLIPSOID && (count += 2) < 5)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[AXIS] +
				tmp->checker[DISTANCE] + tmp->checker[RADIUS]);
	if (check - check_obligate != 0 || check_obligate / count != 1 ||
		tmp->checker[EMISSION_COLOR] + tmp->checker[EMISSION_POWER] == 1)
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
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
