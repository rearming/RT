/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_type_of_parametr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:41:43 by gfoote            #+#    #+#             */
/*   Updated: 2020/03/11 12:41:45 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_parsing.h"

static int	ft_check_material(const char *param, int *type_of_element)
{
	if (ft_strequ(param, "ambient"))
		*type_of_element = AMBIENCE;
	else if (ft_strequ(param, "diffuse"))
		*type_of_element = DIFFUSE;
	else if (ft_strequ(param, "specular"))
		*type_of_element = SPECULAR;
	else if (ft_strequ(param, "emission color"))
		*type_of_element = EMISSION_COLOR;
	else if (ft_strequ(param, "texture position"))
		*type_of_element = TEXTURE_POS;
	else if (ft_strequ(param, "directories"))
		*type_of_element = DIRECTORY;
	return (*type_of_element != NOT_SET) ? 1 : NOT_SET;
}

static int	ft_check(const char *param, int *type_of_element)
{
	if (ft_strequ(param, "rotation"))
		*type_of_element = ROTATION;
	else if (ft_strequ(param, "pos"))
		*type_of_element = POS;
	else if (ft_strequ(param, "direction"))
		*type_of_element = DIRECTION;
	else if (ft_strequ(param, "color"))
		*type_of_element = COLOR;
	else if (ft_strequ(param, "normal"))
		*type_of_element = NORMAL;
	else if (ft_strequ(param, "axis"))
		*type_of_element = AXIS;
	else if (ft_strequ(param, "center"))
		*type_of_element = CENTER;
	else if (ft_strequ(param, "size"))
		*type_of_element = SIZE;
	else if (ft_strequ(param, "vmin"))
		*type_of_element = VMIN;
	else if (ft_strequ(param, "vmax"))
		*type_of_element = VMAX;
	else if (ft_strequ(param, "param_1"))
		*type_of_element = PARAM_1;
	return (*type_of_element != NOT_SET) ? 1 :
	ft_check_material(param, type_of_element);
}

int			ft_type_of_array(int *type_of_element,
		const char *param, int structure_type)
{
	if (ft_strequ(param, "objects"))
		*type_of_element = OBJECT;
	if (ft_strequ(param, "light"))
		*type_of_element = LIGHT;
	if (structure_type == LIGHT)
	{
		if (ft_strequ(param, "ambient"))
			*type_of_element = AMBIENT;
		else if (ft_strequ(param, "point"))
			*type_of_element = POINT;
		else if (ft_strequ(param, "directional"))
			*type_of_element = DIRECTIONAL;
	}
	if (structure_type == OBJECT)
		parse_type2(type_of_element, param);
	return (*type_of_element != NOT_SET) ? 2 :
	(ft_check(param, type_of_element));
}

int			ft_type_of_structure(const char *param, int structure_type)
{
	if (ft_strequ(param, "light"))
		return (LIGHT);
	else if (ft_strequ(param, "camera"))
		return (CAMERA);
	else if (ft_strequ(param, "render parameters"))
		return (RENDER_PARAMS);
	else if (ft_strequ(param, "scene parameters"))
		return (SCENE_PARAMS);
	else if (structure_type == OBJECT && ft_strequ(param, "material"))
		return (MATERIAL);
	else if (structure_type == RENDER_PARAMS)
	{
		if (ft_strequ(param, "pathtrace"))
			return (PATHTRACE);
		else if (ft_strequ(param, "raytrace"))
			return (RAYTRACE);
		else if (ft_strequ(param, "render mesh"))
			return (MESH);
		else if (ft_strequ(param, "textures"))
			return (TEXTURES);
		else if (ft_strequ(param, "skybox"))
			return (SKYBOX);
	}
	return (NOT_SET);
}
