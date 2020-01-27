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
			return (SPECULARITY);
		if (ft_strequ(param, "len"))
			return (LEN);
		if (ft_strequ(param, "angle"))
			return (ANGLE);
		if (ft_strequ(param, "texture"))
			return (TEXTURE);
	}
	return (-1);
}

int		type_of_structure_object(const char *param)
{
	if (ft_strequ(param, "sphere") ||
	(ft_strequ(param, "cone")) ||
	(ft_strequ(param, "cylinder")) ||
	(ft_strequ(param, "plane")))
		return (OBJECT);
	else if (ft_strequ(param, "light"))
		return (LIGHT);
	else if (ft_strequ(param, "camera"))
		return (CAMERA);
	return (-1);
}

int		type_of_object(const char *param, int type)
{
	if (type == OBJECT)
	{
		if (ft_strequ(param, "sphere"))
			return (SPHERE);
		else if (ft_strequ(param, "cone"))
			return (CONE);
		else if (ft_strequ(param, "cylinder"))
			return (CYLINDER);
		else if (ft_strequ(param, "plane"))
			return (PLANE);
	}
	if (type == LIGHT)
	{
		if (ft_strequ(param, "ambient"))
			return (AMBIENT);
		else if (ft_strequ(param, "point"))
			return (POINT);
	}
	if (type == CAMERA && ft_strequ(param, "camera"))
		return (CAMERA);
	return (-1);
}

int		type_of_json_array(const char *param, int type)
{
	if (!param)
		return (-1);
	else if (ft_strequ(param, "pos"))
		return (POS);
	else if (ft_strequ(param, "color"))
		return (COLOR);
	else if (type == CAMERA && ft_strequ(param, "rotation"))
		return (ROTATION);
	else if (type == LIGHT && ft_strequ(param, "direction"))
		return (DIRECTION);
	else if (type == OBJECT)
	{
		if (ft_strequ(param, "normal"))
			return (NORMAL);
		if (ft_strequ(param, "texture_pos"))
			return (TEXTURE_POS);
	}
	return (type_of_structure_object(param));
}
