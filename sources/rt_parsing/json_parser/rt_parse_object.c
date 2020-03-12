/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/03/10 17:07:42 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_parsing.h"

static bool	ft_check(int tmp_stucure_type, int type_of_structure)
{
	if (tmp_stucure_type == RENDER_PARAMS && type_of_structure != OBJECT
		&& type_of_structure != LIGHT && type_of_structure != CAMERA
		&& type_of_structure != SCENE_PARAMS)
		return (true);
	return (false);
}

void		parse_object(t_tmp *tmp, const char *key, json_t *value,
		uint32_t *renderer_flags)
{
	int type_of_structure;

	type_of_structure = ft_type_of_structure(key, tmp->structure_type);
	if (type_of_structure == -1)
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_OBJECT, key));
	if (ft_check(tmp->structure_type, type_of_structure))
		tmp->type = type_of_structure;
	else
	{
		if (type_of_structure == MATERIAL)
			check_duplicated(tmp->checker, type_of_structure);
		else
		{
			if (tmp->structure_type != NOT_SET)
			{
				tmp->next = (t_tmp *)rt_safe_malloc(sizeof(t_tmp));
				init_tmp(tmp->next);
				tmp = tmp->next;
			}
			tmp->structure_type = type_of_structure;
		}
	}
	parse_json_file(value, tmp, renderer_flags);
}
