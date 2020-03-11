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
	int check_zero;

	check_obligate = 0;
	check_zero = 0;
	if (tmp->type == SPHERE)
	{
		check_obligate = (tmp->checker[CENTER] + tmp->checker[RADIUS]) / 2;
		check_zero = tmp->checker[NORMAL] + tmp->checker[DISTANCE] + tmp->checker[AXIS]
				+ tmp->checker[ANGLE] + tmp->checker[LEN] + tmp->checker[VMIN] +
				tmp->checker[VMAX];
	}
	else if (tmp->type == PARABOLOID)
	{
		check_obligate = (tmp->checker[CENTER] + tmp->checker[DISTANCE] + tmp->checker[AXIS]) / 3;
		check_zero = tmp->checker[NORMAL] + tmp->checker[ANGLE] + tmp->checker[LEN]
				+ tmp->checker[VMIN] + tmp->checker[VMAX] + tmp->checker[RADIUS];
	}

}