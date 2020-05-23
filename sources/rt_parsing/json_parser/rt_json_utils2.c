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

int			count_sum(const bool *checker, bool object)
{
	int sum;
	int i;

	sum = 0;
	i = 0;
	if (object)
		sum = checker[NORMAL] + checker[DISTANCE] + checker[AXIS]
			+ checker[ANGLE] + checker[LEN] + checker[VMIN]
			+ checker[VMAX] + checker[CENTER] + checker[RADIUS]
			+ checker[POS] + checker[ROTATION] + checker[INTENSITY]
			+ checker[DIRECTION] + checker[COLOR];
	else
	{
		while (i < (int)sizeof(checker))
		{
			sum += checker[i];
			i++;
		}
	}
	return (sum);
}

void	check_object(t_tmp *tmp)
{
	int check_obligate;
	int check;
	int count;

	count = 2;
	check_obligate = 0;
	check = count_sum(tmp->checker, true);
	if (tmp->type == SPHERE)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[RADIUS]);
	else if (tmp->type == PLANE)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[NORMAL]);
	else if (tmp->type == CONE && ++count < 4)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[AXIS]
			+ tmp->checker[ANGLE]);
	else if (tmp->type == CYLINDER && ++count < 4)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[AXIS]
			+ tmp->checker[RADIUS]);
	else if (tmp->type == PARABOLOID && ++count < 4)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[DISTANCE]
			+ tmp->checker[AXIS]);
	else if (tmp->type == ELLIPSOID && (count += 2) < 5)
		check_obligate = (tmp->checker[CENTER] + tmp->checker[AXIS]
			+ tmp->checker[DISTANCE] + tmp->checker[RADIUS]);
	if (check - check_obligate != 0 || check_obligate / count != 1 ||
		tmp->checker[EMISSION_COLOR] + tmp->checker[EMISSION_POWER] == 1)
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT_PARAMS, object_name(tmp->type)));
	if (tmp->checker[TEXTURE] && !(tmp->type == SPHERE || tmp->type == CONE
		|| tmp->type == CYLINDER || tmp->type == PLANE))
		rt_raise_error(ERR_INVALID_TEXTURE_OBJECT);
	if (tmp->texture_pbr == true)
		if (tmp->checker[TEXTURE] + tmp->checker[TEXTURE_NORMAL] != 2)
			rt_raise_error("wrong initialization of bump_mapping");

}

void	check_camera_or_light(t_tmp *tmp, bool type)
{
	int check_obligate;
	int check;
	int count;

	check = count_sum(tmp->checker, false);
	count = 2;
	if (type)
		check_obligate = tmp->checker[POS] + tmp->checker[ROTATION];
	else
	{
		check_obligate = tmp->checker[INTENSITY] + tmp->checker[COLOR];
		if (tmp->type == DIRECTIONAL && ++count < 4)
			check_obligate += tmp->checker[DIRECTION];
		else if (tmp->type == POINT && ++count < 4)
			check_obligate += tmp->checker[POS];
	}
	if (check_obligate / count != 1 || check - check_obligate != 0)
		(type) ? rt_raise_error(ERR_PARSING_WRONG_CAMERA_PARAMS) :
		rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
}
