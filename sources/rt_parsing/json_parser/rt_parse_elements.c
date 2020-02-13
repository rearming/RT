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

static void	err_type(int structure_type)
{
	if(structure_type == CAMERA)
		rt_raise_error(ERR_PARSING_WRONG_CAMERA_PARAMS);
	else if (structure_type == LIGHT)
		rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
	else
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
}

void	parse_variable(t_tmp *tmp, const char *key, json_t *value)
{
	int variable_type;

	variable_type = type_of_variable(key, tmp->structure_type);
	if (variable_type == -1)
		err_type(tmp->structure_type);
	if ((tmp->checker = ft_check_if_exist(tmp->checker, variable_type)) == -1)
		err_type(tmp->structure_type);
	if (variable_type == INTENSITY)
		tmp->intensity = (float)json_real_value(value);
	else if (variable_type == TYPE)
		tmp->type = json_integer_value(value);
	else if (variable_type == RADIUS)
		tmp->radius = (float)json_real_value(value);
	else if (variable_type == SPECULARITY)
		tmp->specularity = json_integer_value(value);
	else if (variable_type == LEN)
		tmp->len = (float)json_real_value(value);
	else if (variable_type == ANGLE)
		tmp->angle = (float)json_real_value(value);
	else if (variable_type == TEXTURE)
		tmp->texture_number = json_integer_value(value);
	return (0);
}

void	parse_array(t_tmp *tmp, const char *key, json_t *value)
{
	int array_type;
	int array_size;
	int type_of_element;
	int i;

	i = -1;
	array_type = ft_type_of_array(&type_of_element, key);
	if (array_type == 1 || array_type == 2)
	{
		if (array_type == 1)
			tmp->coord_checker = ft_check_if_exist(tmp->coord_checker, type_of_element);
		else
			tmp->material_checker = ft_check_if_exist(tmp->material_checker, type_of_element);
		add_elements_in_array(tmp, type_of_element, array_type, value);
	}
	else if (array_type == 3 || array_type == 4)
	{
		if (array_type == 3)
		{
			if (tmp->structure_type == NOT_SET && type_of_element == LIGHT)
				tmp->structure_type = type_of_element;
			else if (tmp->type == LIGHT && type_of_element != LIGHT)
				tmp->type = type_of_element;
			else
				rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
		}
		else
		{
			if (tmp->structure_type == NOT_SET && type_of_element == OBJECT)
				tmp->structure_type = type_of_element;
			else if (tmp->type == OBJECT && type_of_element != OBJECT)
				tmp->type = type_of_element;
			else
				rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
		}
		array_size = json_array_size(value);
		while (++i < array_size)
		{
			tmp->next = (t_tmp *) malloc(sizeof(t_tmp));
			copy_tmp(tmp->next, *tmp);
			tmp = tmp->next;
		}
		parse_json_file(json_array_get(value, i), tmp);
	}
}

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
