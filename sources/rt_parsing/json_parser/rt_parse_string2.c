/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_string2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_parsing.h"

static void	parse_type3(int *type, const char *value)
{
	if (ft_strequ(value, "torus"))
		*type = TORUS;
	else if (ft_strequ(value, "ellipsoid raymarch"))
		*type = ELLIPSOID_RAYMARCH;
	else if (ft_strequ(value, "torus capped"))
		*type = TORUS_CAPPED;
	else if (ft_strequ(value, "cylinder raymarch"))
		*type = CYLINDER_RAYMARCH;
	else if (ft_strequ(value, "round cone"))
		*type = ROUND_CONE;
	else if (ft_strequ(value, "test object"))
		*type = TEST_OBJECT;
}

void		parse_type2(int *type, const char *value)
{
	if (ft_strequ(value, "sphere"))
		*type = SPHERE;
	else if (ft_strequ(value, "cone"))
		*type = CONE;
	else if (ft_strequ(value, "cylinder"))
		*type = CYLINDER;
	else if (ft_strequ(value, "plane"))
		*type = PLANE;
	else if (ft_strequ(value, "AABB"))
		*type = AABB;
	else if (ft_strequ(value, "triangle"))
		*type = TRIANGLE;
	else if (ft_strequ(value, "paraboloid"))
		*type = PARABOLOID;
	else if (ft_strequ(value, "ellipsoid"))
		*type = ELLIPSOID;
	else if (ft_strequ(value, "box"))
		*type = BOX;
	else if (ft_strequ(value, "capsule"))
		*type = CAPSULE;
	else
		parse_type3(type, value);
}
