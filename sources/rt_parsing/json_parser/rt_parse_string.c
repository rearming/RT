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
static uint32_t search_cl_parameters(const char *tmp_value)
{
	if (ft_strequ(tmp_value, "RENDER_RAYTRACE"))
		return RENDER_RAYTRACE;
	else if (ft_strequ(tmp_value, "RENDER_PATHTRACE"))
		return RENDER_PATHTRACE;
	if (ft_strequ(tmp_value, "RENDER_RAYMARCH"))
		return RENDER_RAYMARCH;
	else if (ft_strequ(tmp_value, "RENDER_MESH"))
		return RENDER_MESH;
	if (ft_strequ(tmp_value, "RENDER_BACKFACE_CULLING"))
		return RENDER_BACKFACE_CULLING;
	else if (ft_strequ(tmp_value, "RENDER_OBJECTS"))
		return RENDER_OBJECTS;
	if (ft_strequ(tmp_value, "RENDER_MESH_VTEXTURES"))
		return RENDER_MESH_VTEXTURES;
	else if (ft_strequ(tmp_value, "RENDER_TEXTURES"))
		return RENDER_TEXTURES;
	else
		rt_raise_error(ERR_PARSING_WRONG_CL_PARAM);
	return (-1);
}

static void parse_cl_parameters(const char *tmp_value, uint32_t *renderer_flags){

	char **cl_parameters;
	uint32_t tmp;
	int i;

	tmp = 0;
	i = 0;
	cl_parameters = ft_strsplit(tmp_value, '|');
	while (cl_parameters[i])
	{
		tmp = search_cl_parameters(ft_strtrim(cl_parameters[i])) | tmp;
		i++;
	}
	ft_strdel(cl_parameters);
	*renderer_flags = tmp;
}

static void	parse_material(t_tmp *tmp, const char *key, const char *tmp_value)
{
	if (ft_strequ(key, "diffuse"))
	{
		check_duplicated(tmp->checker, DIFFUSE);
		tmp->diffuse = get_float3_color(hex_to_int(tmp_value));
	}
	else if (ft_strequ(key, "specular"))
	{
		check_duplicated(tmp->checker, SPECULAR);
		tmp->specular = get_float3_color(hex_to_int(tmp_value));
	}
	else if (ft_strequ(key, "color"))
	{
		check_duplicated(tmp->checker, COLOR);
		tmp->color = get_float3_color(hex_to_int(tmp_value));
	}
	else if (ft_strequ(key, "emission color"))
	{
		check_duplicated(tmp->checker, EMISSION_COLOR);
		tmp->emission_color = get_float3_color(hex_to_int(tmp_value));
	}
	else if (ft_strequ(key, "texture"))
	{
		check_duplicated(tmp->checker, TEXTURE);
		tmp->texture_number = parse_texture(tmp_value);
	}
}

static void	parse_type(t_tmp *tmp, const char *value)
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
		else
			rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_TYPE);
}

void		parse_string(t_tmp *tmp, const char *key, json_t *value, const uint32_t *renderer_flags)
{
	const char *tmp_value;

	tmp_value = json_string_value(value);
	if (tmp->structure_type == NOT_SET)
	{
		if (ft_strequ(key, "open cl parameters"))
			{
				if (renderer_flags == 0)
					rt_raise_error(ERR_PARSING_DUPLICATED_PARAM);
				parse_cl_parameters(tmp_value, renderer_flags);
			}
		else if (ft_strequ(key, "skybox"))
			ft_add_texture_name_back(&g_textures.textures_names, tmp_value);
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
