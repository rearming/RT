/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:19:51 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:19:53 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_check_if_exist(int checker, int type)
{
	if (type == 2 || type == 20 || type == 200 ||type == 2000
	|| type == 20000 || type == 200000 || type == 2000000
	|| type == 20000000)
	{
		if (checker / (type / 2) % 10 == 0)
		return (checker + type);
	}
	else
	{
		if (checker / type % 10 == 0)
			return (checker + type);
	}
	return (-1);
}

int		ft_check_is_object_parsed(int checker, int structure_type, int type)
{
	if (structure_type == CAMERA)
	{
		if (checker != 32)
			return (-1); //error
		else
			return (1); //finishes
	}
	else if (structure_type == LIGHT)
	{
		if ((type == AMBIENT && checker == 10110) ||
			(type == POINT && checker == 10112))
			return (1);
		return (0); //continue;
	}
	else if (structure_type == OBJECT)
	{
		if ((type == CONE && (checker == 1010222 || checker == 1220222)) ||
			(type == SPHERE && (checker == 12202 || checker == 222202)) ||
			(type == CYLINDER && (checker == 13222 || checker == 223222)) ||
			(type == PLANE && (checker == 10222 || checker == 220222)))
			return (1);
		return (0);
	}
	return (-1);
}
