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

static uint32_t	search_cl_parameters(const char *tmp_value)
{
	if (ft_strequ(tmp_value, "RENDER_RAYTRACE"))
		return (RENDER_RAYTRACE);
	else if (ft_strequ(tmp_value, "RENDER_PATHTRACE"))
		return (RENDER_PATHTRACE);
	if (ft_strequ(tmp_value, "RENDER_RAYMARCH"))
		return (RENDER_RAYMARCH);
	else if (ft_strequ(tmp_value, "RENDER_MESH"))
		return (RENDER_MESH);
	if (ft_strequ(tmp_value, "RENDER_BACKFACE_CULLING"))
		return (RENDER_BACKFACE_CULLING);
	else if (ft_strequ(tmp_value, "RENDER_OBJECTS"))
		return (RENDER_OBJECTS);
	if (ft_strequ(tmp_value, "RENDER_MESH_VTEXTURES"))
		return (RENDER_MESH_VTEXTURES);
	else if (ft_strequ(tmp_value, "RENDER_TEXTURES"))
		return (RENDER_TEXTURES);
	else if (ft_strequ(tmp_value, "RENDER_ANTI_ALIASING"))
		return (RENDER_ANTI_ALIASING);
	else
		rt_raise_error(ERR_PARSING_WRONG_CL_PARAM);
	return (-1);
}

static void		parse_cl_parameters(const char *tmp_value,
		uint32_t *renderer_flags)
{
	char		**cl_parameters;
	uint32_t	flags;
	char		*tmp_trimd;
	int			i;

	flags = 0;
	i = 0;
	cl_parameters = ft_strsplit(tmp_value, '|');
	while (cl_parameters[i])
	{
		tmp_trimd = ft_strtrim(cl_parameters[i]);
		flags = search_cl_parameters(tmp_trimd) | flags;
		free(tmp_trimd);
		i++;
	}
	i = 0;
	while (cl_parameters[i])
	{
		ft_strclr(cl_parameters[i]);
		free(cl_parameters[i]);
		i++;
	}
	free(cl_parameters);
	*renderer_flags = flags;
}

static void		parse_material(t_tmp *tmp, const char *key,
		const char *tmp_value)
{
	if (ft_strequ(key, "diffuse"))
	{
		check_duplicated(tmp->checker, DIFFUSE);
//        tmp->diffuse = get_float3_color(hex_to_int(tmp_value));
//        printf("diffuse = [%.3f][%.3f][%.3f], \n", tmp->diffuse.x, tmp->diffuse.y, tmp->diffuse.z);
        tmp->diffuse = get_float3_color((int)strtol(tmp_value, NULL, 16));
//        printf("diffuse = [%.3f][%.3f][%.3f], \n", tmp->diffuse.x, tmp->diffuse.y, tmp->diffuse.z);
	}
	else if (ft_strequ(key, "specular"))
	{
		check_duplicated(tmp->checker, SPECULAR);
		tmp->specular = get_float3_color((int)strtol(tmp_value, NULL, 16));
	}
	else if (ft_strequ(key, "emission color"))
	{
		check_duplicated(tmp->checker, EMISSION_COLOR);
		tmp->emission_color = get_float3_color((int)strtol(tmp_value, NULL, 16));
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
		else if (ft_strequ(value, "directional"))
			tmp->type = DIRECTIONAL;
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
		else if (ft_strequ(value, "triangle"))
			tmp->type = TRIANGLE;
		else if (ft_strequ(value, "paraboloid"))
			tmp->type = PARABOLOID;
		else if (ft_strequ(value, "ellipsoid"))
			tmp->type = ELLIPSOID;
		else
			rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_TYPE);
}

void			parse_string(t_tmp *tmp, const char *key, json_t *value,
		uint32_t *renderer_flags)
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
			{
				if(g_textures.skybox_info->skybox_exist == true)
					rt_raise_error("duplicated skybox");
				g_textures.skybox_info->skybox_exist = true;
				g_textures.skybox_info->skybox_name = ft_strdup(tmp_value);
				printf("%s\n", g_textures.skybox_info->skybox_name);
			}
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
