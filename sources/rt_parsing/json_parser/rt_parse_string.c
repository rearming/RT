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
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_TYPE);
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
	else if (ft_strequ(key, "texture normal"))
	{
		check_duplicated(tmp->checker, TEXTURE_NORMAL);
		tmp->texture_normal = parse_texture(tmp_value);
	}
}

static void		parse_type(t_tmp *tmp, const char *value)
{
	if (tmp->struct_type == LIGHT)
	{
		if (ft_strequ(value, "ambient"))
			tmp->type = AMBIENT;
		else if (ft_strequ(value, "point"))
			tmp->type = POINT;
		else if (ft_strequ(value, "directional"))
			tmp->type = DIRECTIONAL;
		else
			rt_raise_error(ERR_PARSING_WRONG_LIGHT_PARAMS);
	}
	else if (tmp->struct_type == OBJECT)
		parse_type2(tmp, value);
	else
		rt_raise_error(ERR_PARSING_WRONG_TYPE);
}

static void		parse_string2(t_tmp *tmp, const char *key,
		const char *tmp_value)
{
	if (ft_strequ(key, "texture") && tmp->type == SKYBOX)
	{
		if (g_textures.skybox_info->skybox_exist == true)
			rt_raise_error(ERR_PARSING_DUPLICATED_SKYBOX);
		g_textures.skybox_info->skybox_exist = true;
		g_textures.skybox_info->skybox_name = ft_strdup(tmp_value);
	}
	else if (ft_strequ(key, "directory"))
	{
		g_textures.folders_names = rt_safe_malloc(1);
		g_textures.folders_names[0] = ft_strdup(tmp_value);
		g_textures.folders_names[1] = NULL;
	}
}

void			parse_string(t_tmp *tmp, const char *key, json_t *value,
		uint32_t *renderer_flags)
{
	const char *tmp_value;

	tmp_value = json_string_value(value);
	if (tmp->struct_type == RENDER_PARAMS)
	{
		if (ft_strequ(key, "render algorithm") &&
		(ft_strequ(tmp_value, "pathtrace") || ft_strequ(tmp_value, "raytrace")))
			*renderer_flags = ft_strequ(tmp_value, "pathtrace") ?
				*renderer_flags | RENDER_PATHTRACE :
				*renderer_flags | RENDER_RAYTRACE;
		else if ((ft_strequ(key, "texture") && tmp->type == SKYBOX) ||
			ft_strequ(key, "directory"))
			parse_string2(tmp, key, tmp_value);
		else if (ft_strequ(key, "file"))
			tmp->file = ft_strdup(tmp_value);
		else
			rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_PARAM, tmp_value));
	}
	else if (tmp->type == NOT_SET && ft_strequ(key, "type"))
		parse_type(tmp, tmp_value);
	else if (tmp->struct_type != NOT_SET && tmp->type != NOT_SET)
		parse_material(tmp, key, tmp_value);
	else
		rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_PARAM, tmp_value));
}
