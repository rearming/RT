/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:57:25 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/27 15:57:32 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_math_utils.h"

void 		parse_string(t_tmp *tmp, const char *key, json_t *value)
{
	const char *tmp_value;

	tmp_value = json_string_value(value);
	if (tmp->type == NOT_SET && ft_strequ(key, "type"))
	{
		if (tmp->structure_type == LIGHT)
		{
			if (ft_strequ(tmp_value, "ambient"))
				tmp->type = AMBIENT;
			else if (ft_strequ(tmp_value, "point"))
				tmp->type = POINT;
			else
				rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
		}
		else if (tmp->structure_type == OBJECT)
		{
			if (ft_strequ(tmp_value, "sphere"))
				tmp->type = SPHERE;
			else if (ft_strequ(tmp_value, "cone"))
				tmp->type = CONE;
			else if (ft_strequ(tmp_value, "cylinder"))
				tmp->type = CYLINDER;
			else if (ft_strequ(tmp_value, "plane"))
				tmp->type = PLANE;
			else
				rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
		}
		else
			rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
	}
	else if (ft_strequ(key, "diffuse"))
		tmp->diffuse = get_float3_color(ft_atoi(tmp_value));
	else if (ft_strequ(key, "color"))
		tmp->color = get_float3_color(ft_atoi(tmp_value));
	/*else if (ft_strequ(key, "texture"))
	{

	}*/
	else
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
}