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

void		parse_object(t_tmp *tmp, const char *key, json_t *value)
{
	int type_of_structure;

	type_of_structure = ft_type_of_structure(key);
	if (type_of_structure != -1)
	{
		if (type_of_structure == MATERIAL)
			tmp->coord_checker = ft_check_if_exist(tmp->coord_checker, MATERIAL);
		else
		{
			if (tmp->structure_type == NOT_SET)
				tmp->structure_type = type_of_structure;
			else
			{
				tmp->next = (t_tmp *) rt_safe_malloc(sizeof(t_tmp));
				init_tmp(tmp->next);
				tmp = tmp->next;
				tmp->structure_type = type_of_structure;
			}
		}
		parse_json_file(value, tmp);
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_PARAM);
}

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
	/*else if (ft_strequ(key, "texture"))
	{

	}*/
	else
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
}