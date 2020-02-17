/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:19:44 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:19:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	add_array(cl_float3 *elem, json_t *value)
{
	json_t	*tmp;
	int		i;

	i = -1;
	if (json_array_size(value) == 3)
	{
		while (++i < 3)
		{
			tmp = json_array_get(value, i);
			if (!json_is_number(tmp))
				printf("error");
			else
				elem->s[i] = json_is_integer(tmp) ? json_integer_value(tmp)
					: json_real_value(tmp);
		}
	}
}

static void	add_elements_in_array(t_tmp *tmp, int type_of_element,
		json_t *value)
{
	if (type_of_element == POS)
		add_array(&tmp->pos, value);
	else if (type_of_element == ROTATION)
		add_array(&tmp->rotation, value);
	else if (type_of_element == DIRECTION)
		add_array(&tmp->dir, value);
	else if (type_of_element == COLOR)
		add_array(&tmp->color, value);
	else if (type_of_element == NORMAL)
		add_array(&tmp->normal, value);
	else if (type_of_element == TEXTURE_POS)
		add_array(&tmp->texture_position, value);
	if (type_of_element == AMBIENCE)
		add_array(&tmp->ambience, value);
	else if (type_of_element == DIFFUSE)
		add_array(&tmp->diffuse, value);
	else
		add_array(&tmp->specular, value);
}

void	parse_array(t_tmp *tmp, const char *key, json_t *value)
{
	int array_type;
	int array_size;
	int type_of_element;
	int type_of_structure;
	int i;

	i = -1;
	type_of_element = -1;
	array_type = ft_type_of_array(&type_of_element, key, tmp->structure_type);
	if (array_type == 1)
	{
		if (tmp->checker[type_of_element] == true)
			rt_raise_error(ERR_PARSING_WRONG_PARAM);
		else
			tmp->checker[type_of_element] = true;
		add_elements_in_array(tmp, type_of_element, value);
	}
	else if (array_type == 2)
	{
		if (type_of_element != LIGHT && type_of_element != OBJECT)
			type_of_structure = tmp->structure_type;
		else
			type_of_structure = type_of_element;
		array_size = json_array_size(value);
		while (++i < array_size)
		{
			tmp->next = (t_tmp *) malloc(sizeof(t_tmp));
			init_tmp(tmp->next);
			tmp = tmp->next;
			if (type_of_structure != type_of_element)
			{
				tmp->structure_type = type_of_structure;
				tmp->type = type_of_element;
			} else
				tmp->structure_type = type_of_structure;
			parse_json_file(json_array_get(value, i), tmp);
		}
	} else
		rt_raise_error(ERR_PARSING_WRONG_PARAM);

}
