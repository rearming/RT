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

static void add_array_color(cl_float3 *elem, json_t *value)
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
				rt_raise_error(ERR_PARSING_WRONG_FORMAT);
			else if (json_is_integer(tmp))
				elem->s[i] = (float)(json_integer_value(tmp) / 255.0);
			else
				elem->s[i] = json_real_value(tmp);
		}
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_PARAM);
}

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
				rt_raise_error(ERR_PARSING_WRONG_FORMAT);
			else
				elem->s[i] = json_is_integer(tmp) ? json_integer_value(tmp)
					: json_real_value(tmp);
		}
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_PARAM);
}

static void	add_elements_in_array_material(t_tmp *tmp,
		int type_of_element, json_t *value)
{
	if (type_of_element == AMBIENCE)
		add_array(&tmp->ambience, value);
	else if (type_of_element == DIFFUSE)
		add_array_color(&tmp->diffuse, value);
	else if (type_of_element == SPECULAR)
		add_array_color(&tmp->specular, value);
	else if (type_of_element == EMISSION_COLOR)
		add_array_color(&tmp->emission_color, value);
	else if (type_of_element == TEXTURE_POS)
		add_array(&tmp->texture_position, value);
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
		add_array_color(&tmp->color, value);
	else if (type_of_element == NORMAL)
		add_array(&tmp->normal, value);
	else if (type_of_element == AXIS)
		add_array(&tmp->axis, value);
	else if (type_of_element == CENTER)
		add_array(&tmp->center, value);
	else if (type_of_element == VMIN)
		add_array(&tmp->vmin, value);
	else if (type_of_element == VMAX)
		add_array(&tmp->vmax, value);
	else
		add_elements_in_array_material(tmp, type_of_element, value);
}

static void	parse_array2(t_tmp *tmp, int type_of_element, json_t *value,
		uint32_t *renderer_flags)
{
	int i;
	int type_of_structure;
	int array_size;

	i = -1;
	type_of_structure = (type_of_element != LIGHT &&
		type_of_element != OBJECT) ? tmp->structure_type : type_of_element;
	array_size = json_array_size(value);
	while (++i < array_size)
	{
		if (tmp->structure_type != -1)
		{
			tmp->next = rt_safe_malloc(sizeof(t_tmp));
			init_tmp(tmp->next);
			tmp = tmp->next;
		}
		tmp->structure_type = type_of_structure;
		if (type_of_structure != type_of_element)
			tmp->type = type_of_element;
		parse_json_file(json_array_get(value, i), tmp, renderer_flags);
	}
}

void		parse_array(t_tmp *tmp, const char *key, json_t *value,
		uint32_t *renderer_flags)
{
	int array_type;
	int type_of_element;

	type_of_element = -1;
	array_type = ft_type_of_array(&type_of_element, key, tmp->structure_type);
	if (array_type == 1)
	{
		check_duplicated(tmp->checker, type_of_element);
		add_elements_in_array(tmp, type_of_element, value);
	}
	else if (array_type == 2)
		parse_array2(tmp, type_of_element, value, renderer_flags);
	else
		rt_raise_error(ERR_PARSING_WRONG_TYPE);
}
