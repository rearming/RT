/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_parsing.h"

static float	parse(json_t *value, bool *checker, int number)
{
	check_duplicated(checker, number);
	return (json_is_integer(value) ?
	((float)json_integer_value(value)) : ((float)json_real_value(value)));
}

static void		parse_variable_material2(t_tmp *tmp, const char *key,
		json_t *value)
{
	if (ft_strequ(key, "refraction"))
		tmp->refraction = parse(value, tmp->checker, REFRACTION);
	else if (ft_strequ(key, "emission power"))
		tmp->emission_power = parse(value, tmp->checker, EMISSION_POWER);
	else if (ft_strequ(key, "specular texture"))
		tmp->specular_texture = parse(value, tmp->checker, SPECULAR_TEXTURE);
	else if (ft_strequ(key, "gamma"))
		tmp->gamma = parse(value, tmp->checker, GAMMA);
	else if (ft_strequ(key, "alfa angle"))
		tmp->alfa_angle = parse(value, tmp->checker, ALFA_ANGLE);
	else if (ft_strequ(key, "beta angle"))
		tmp->beta_angle = parse(value, tmp->checker, BETA_ANGLE);
	else if (ft_strequ(key, "gamma angle"))
		tmp->gamma_angle = parse(value, tmp->checker, GAMMA_ANGLE);
	else if (ft_strequ(key, "param_0"))
		tmp->gamma_angle = parse(value, tmp->checker, PARAM_0);
	else if (ft_strequ(key, "pbr index"))
		tmp->texture_pbr_index = parse(value, tmp->checker, TEXTURE_PBR_INDEX);
	else
		rt_raise_error(ft_strjoin(ERR_PARS_WRONG_PRM, key));
}

static void		parse_variable_material1(t_tmp *tmp, const char *key,
		json_t *value)
{
	if (ft_strequ(key, "phong exp"))
		tmp->phong_exp = parse(value, tmp->checker, PHONG_EXP);
	else if (ft_strequ(key, "smoothness"))
		tmp->smoothness = parse(value, tmp->checker, SMOOTHNESS);
	else if (ft_strequ(key, "transmittance"))
		tmp->transmittance = parse(value, tmp->checker, TRANSMITTANCE);
	else
		parse_variable_material2(tmp, key, value);
}

static void		parse_variable_params(t_tmp *tmp, const char *key,
		json_t *value)
{
	if (ft_strequ(key, "distance"))
		tmp->distance = parse(value, tmp->checker, DISTANCE);
	else if (ft_strequ(key, "radius"))
		tmp->radius = parse(value, tmp->checker, RADIUS);
	else if (ft_strequ(key, "radius 2"))
		tmp->radius_2 = parse(value, tmp->checker, RADIUS_2);
	else if (ft_strequ(key, "radius ring"))
		tmp->radius_ring = parse(value, tmp->checker, RADIUS_RING);
	else if (ft_strequ(key, "angle"))
		tmp->angle = parse(value, tmp->checker, ANGLE);
	else if (ft_strequ(key, "len"))
		tmp->len = parse(value, tmp->checker, LEN);
	else
		parse_variable_material1(tmp, key, value);
}

void			parse_variable(t_tmp *tmp, const char *key, json_t *value)
{
	if (ft_strequ(key, "type"))
	{
		check_duplicated(tmp->checker, TYPE);
		tmp->type = json_integer_value(value);
	}
	else if (ft_strequ(key, "intensity"))
		tmp->intensity = parse(value, tmp->checker, INTENSITY);
	else if (ft_strequ(key, "exposure"))
		tmp->exposure = parse(value, tmp->checker, EXPOSURE);
	else if (ft_strequ(key, "raymarch index"))
	{
		check_duplicated(tmp->checker, RAYMARCH_INDEX);
		tmp->raymarch_index = json_integer_value(value);
	}
	else if (ft_strequ(key, "max light bounces") && (tmp->type == RAYTRACE ||
	tmp->type == PATHTRACE))
	{
		if (tmp->type == RAYTRACE)
			tmp->max_depth_r = json_integer_value(value);
		else
			tmp->max_depth_p = json_integer_value(value);
	}
	else
		parse_variable_params(tmp, key, value);
}
