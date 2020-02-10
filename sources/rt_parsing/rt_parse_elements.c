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

int	parse_variable(t_tmp *tmp, const char *key, json_t *value)
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

int	parse_array_elems(t_tmp *tmp, int array_type, json_t *value)
{
	if ((tmp->checker = ft_check_if_exist(tmp->checker, array_type)) == -1)
		err_type(tmp->structure_type);
	if (array_type == POS)
		add_array(&tmp->pos, value);
	else if (array_type == ROTATION)
		add_array(&tmp->rotation, value);
	else if (array_type == NORMAL)
		add_array(&tmp->normal, value);
	else if (array_type == TEXTURE_POS)
		add_array(&tmp->texture_position, value);
	return (0);
}

int	parse_array(t_tmp *tmp, const char *key, json_t *value)
{
	int	array_type;
	int array_size;
	int i;

	i = -1;
	if (tmp->structure_type == 0)
		tmp->structure_type = type_of_structure_object(key);
	array_type = type_of_json_array(key, tmp->structure_type);
	if (array_type == CAMERA)
		rt_raise_error(ERR_PARSING_WRONG_CAMERA_PARAMS);
	else if (array_type == OBJECT || array_type == LIGHT)
	{
		array_size = json_array_size(value);
		while (++i < array_size)
		{
			if (tmp->checker != 0)
			{
				tmp->next = (t_tmp *)malloc(sizeof(t_tmp));
				init_tmp(tmp->next);
				tmp->next->structure_type = array_type;
				tmp = tmp->next;
			}
			if (array_type == OBJECT)
				tmp->type = type_of_object(key, array_type);
			parse_json_file(json_array_get(value, i), tmp);
		}
	}
	else if (parse_array_elems(tmp, array_type, value) == -1)
		return (-1);
	return (0);
}

int	parse_object(t_tmp *tmp, const char *key, json_t *value)
{
	t_tmp tmp2;

	init_tmp(&tmp2);
	tmp2.structure_type = type_of_structure_object(key);
	if (tmp->structure_type == -1)
		rt_raise_error(ERR_PARSING_WRONG_PARAM);
	if (tmp2.structure_type != LIGHT)
	{
		tmp2.type = type_of_object(key, tmp2.structure_type);
		if (tmp2.type == -1)
			rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
	}
	if (tmp->checker != 0)
	{
		tmp->next = (t_tmp *)rt_safe_malloc(sizeof(t_tmp));
		init_tmp(tmp->next);
		tmp = tmp->next;
	}
	tmp->structure_type = tmp2.structure_type;
	tmp->type = tmp2.type;
	parse_json_file(value, tmp);
}


