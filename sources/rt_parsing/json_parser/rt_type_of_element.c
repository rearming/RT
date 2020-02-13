/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:14:49 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:20:28 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		type_of_variable(const char *param, int type)
{
	if (!param)
		return (-1);
	if (type == LIGHT)
	{
		if (ft_strequ(param, "intensity"))
			return (INTENSITY);
		else if (ft_strequ(param, "type"))
			return (TYPE);
	}
	else if (type == OBJECT)
	{
		if (ft_strequ(param, "radius"))
			return (RADIUS);
		else if (ft_strequ(param, "specularity"))
			return (SPECULAR);
		if (ft_strequ(param, "len"))
			return (LEN);
		if (ft_strequ(param, "angle"))
			return (ANGLE);
		if (ft_strequ(param, "texture"))
			return (TEXTURE);
	}
	return (-1);
}
