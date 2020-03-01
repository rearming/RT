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
#include "rt_parsing.h"

static void		parse_type2(t_tmp *tmp, const char *value)
{
	if (ft_strequ(value, "sphere"))
		tmp->type = SPHERE;
	else if (ft_strequ(value, "cone"))
		tmp->type = CONE;
	else if (ft_strequ(value, "cylinder"))
		tmp->type = CYLINDER;
	else if (ft_strequ(value, "plane"))
		tmp->type = PLANE;
	else if (ft_strequ(value, "AABB"))
		tmp->type = AABB;
	else if (ft_strequ(value, "triangle"))
		tmp->type = TRIANGLE;
	else if (ft_strequ(value, "paraboloid"))
		tmp->type = PARABOLOID;
	else if (ft_strequ(value, "ellipsoid"))
		tmp->type = ELLIPSOID;
	else
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
}

static void		parse_material(t_tmp *tmp, const char *key,
		const char *tmp_value)
{
	if (ft_strequ(key, "diffuse"))
	{
		check_duplicated(tmp->checker, DIFFUSE);
		tmp->diffuse = get_float3_color((int)strtol(tmp_value, NULL, 16));
	}
	else if (ft_strequ(key, "specular"))
	{
		check_duplicated(tmp->checker, SPECULAR);
		tmp->specular = get_float3_color((int)strtol(tmp_value, NULL, 16));
	}
	else if (ft_strequ(key, "color"))
	{
		check_duplicated(tmp->checker, COLOR);
		tmp->color = get_float3_color((int)strtol(tmp_value, NULL, 16));
	}
	else if (ft_strequ(key, "emission color"))
	{
		check_duplicated(tmp->checker, EMISSION_COLOR);
		tmp->emission_color = get_float3_color((int)strtol(tmp_value, 0, 16));
	}
	else if (ft_strequ(key, "texture"))
	{
		check_duplicated(tmp->checker, TEXTURE);
		tmp->texture_number = parse_texture(tmp_value);
	}
}

static void		parse_type(t_tmp *tmp, const char *value)
{
	if (tmp->structure_type == LIGHT)
	{
		if (ft_strequ(value, "ambient"))
			tmp->type = AMBIENT;
		else if (ft_strequ(value, "point"))
			tmp->type = POINT;
		else
			rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
	}
	else if (tmp->structure_type == OBJECT)
		parse_type2(tmp, value);
	else
		rt_raise_error(ERR_PARSING_WRONG_TYPE);
}

void			parse_string(t_tmp *tmp, const char *key, json_t *value,
		uint32_t *renderer_flags)
{
	const char *tmp_value;

	tmp_value = json_string_value(value);
	if (tmp->structure_type == RENDER_PARAMETERS)
	{
		if (ft_strequ(key, "render algorithm") &&
		(ft_strequ(tmp_value, "pathtrace") || ft_strequ(tmp_value, "raytrace")))
			*renderer_flags = ft_strequ(tmp_value, "pathtrace") ?
				*renderer_flags | RENDER_PATHTRACE :
				*renderer_flags | RENDER_RAYTRACE;
		else if (ft_strequ(key, "skybox"))
			{
				if(g_textures.skybox_info->skybox_exist == true)
					rt_raise_error(ERR_PRSING_DUPLICATED_SKYBOX);
				g_textures.skybox_info->skybox_exist = true;
				g_textures.skybox_info->skybox_name = ft_strdup(tmp_value);
				printf("%s\n", g_textures.skybox_info->skybox_name);
			}
		else if (ft_strequ(key, "file"))
			printf("here add obj file\n");
		else if (ft_strequ(key, "directory"))
			printf("here add directories\n");
		else
			rt_raise_error(ERR_PARSING_WRONG_TYPE);
	}
	else if (tmp->type == NOT_SET && ft_strequ(key, "type"))
		parse_type(tmp, tmp_value);
	else if (tmp->structure_type != NOT_SET && tmp->type != NOT_SET)
		parse_material(tmp, key, tmp_value);
	else
		rt_raise_error(ERR_PARSING_WRONG_TYPE);
}
