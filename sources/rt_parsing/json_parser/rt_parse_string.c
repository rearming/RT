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

static void	parse_parameters(t_tmp *tmp, const char *key, const char *tmp_value)
{
	if (ft_strequ(key, "diffuse"))
	{
		check_duplicated(tmp->checker, DIFFUSE);
		tmp->diffuse = get_float3_color(ft_atoi(tmp_value));
	}
	else if (ft_strequ(key, "specular"))
	{
		check_duplicated(tmp->checker, SPECULAR);
		tmp->specular = get_float3_color(ft_atoi(tmp_value));
	}
	else if (ft_strequ(key, "color"))
	{
		check_duplicated(tmp->checker, COLOR);
		tmp->color = get_float3_color(ft_atoi(tmp_value));
	}
	else if (ft_strequ(key, "emission color"))
	{
		check_duplicated(tmp->checker, EMISSION_COLOR);
		tmp->emission_color = get_float3_color(ft_atoi(tmp_value));
	}
	else if (ft_strequ(key, "texture"))
	{
		check_duplicated(tmp->checker, TEXTURE);
		tmp->texture_number = parse_texture(tmp_value);
	}
}

static void parse_type(t_tmp *tmp, const char *value)
{
	if (tmp->structure_type == LIGHT)
	{
		if (ft_strequ(value, "ambient"))
			tmp->type = AMBIENT;
		else if (ft_strequ(value, "point"))
			tmp->type = POINT;
		else
			rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
	}
	else if (tmp->structure_type == OBJECT)
	{
		if (ft_strequ(value, "sphere"))
			tmp->type = SPHERE;
		else if (ft_strequ(value, "cone"))
			tmp->type = CONE;
		else if (ft_strequ(value, "cylinder"))
			tmp->type = CYLINDER;
		else if (ft_strequ(value, "plane"))
			tmp->type = PLANE;
		else
			rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
}

void		parse_string(t_tmp *tmp, const char *key, json_t *value)
{
	const char *tmp_value;

	tmp_value = json_string_value(value);
	if (tmp->structure_type == NOT_SET)
	{
		if (ft_strequ(key, "open cl parameters"))
			printf("open cl parameters\n");
		else if (ft_strequ(key, "skybox"))
			ft_add_texture_name_back(&g_textures.textures_names, tmp_value);
		else
			rt_raise_error(ERR_PARSING_WRONG_PARAM);
	}
	else if (tmp->type == NOT_SET && ft_strequ(key, "type"))
		parse_type(tmp, tmp_value);
	else if (tmp->structure_type != NOT_SET && tmp->type != NOT_SET)
		parse_parameters(tmp, key, tmp_value);
	else
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
}
