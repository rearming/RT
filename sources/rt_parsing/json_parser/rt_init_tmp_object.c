/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:19:30 by gfoote            #+#    #+#             */
/*   Updated: 2020/01/24 15:19:33 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_math_utils.h"

void		init_tmp(t_tmp *tmp)
{
	tmp->next = NULL;
	tmp->structure_type = NOT_SET;
	tmp->type = NOT_SET;
	tmp->pos = get_float3_color(COL_NOT_SET);
	tmp->rotation = get_float3_color(COL_NOT_SET);
	tmp->intensity = NOT_SET;
	tmp->dir = get_float3_color(COL_NOT_SET);
	tmp->color = get_float3_color(COL_NOT_SET);
	tmp->normal = get_float3_color(COL_NOT_SET);
	tmp->radius = NOT_SET;
	tmp->angle = NOT_SET;
	tmp->len = NOT_SET;
	tmp->ambience = (cl_float3){{0, 0, 0}};
	tmp->diffuse = (cl_float3){{0, 0, 0}};
	tmp->specular = (cl_float3){{0, 0, 0}};
	tmp->phong_exp = 0;
	tmp->smoothness = 0;
	tmp->transmittance = 0;
	tmp->refraction = 0;
	tmp->emission_power = 0;
	tmp->specular_texture = 0;
	tmp->texture_number = NOT_SET;
	tmp->texture_position = (cl_float3){{0, 0, 0}};
	tmp->coord_checker = 0;
	tmp->material_checker = 0;
}

void		copy_tmp(t_tmp *tmp, t_tmp tmp_source)
{
	tmp->structure_type = tmp_source.structure_type;
	tmp->type = tmp_source.type;
	tmp->pos = tmp_source.pos;
	tmp->rotation = tmp_source.rotation;
	tmp->intensity = tmp_source.intensity;
	tmp->dir = tmp_source.dir;
	tmp->color = tmp_source.color;
	tmp->normal = tmp_source.normal;
	tmp->radius = tmp_source.radius;
	tmp->angle = tmp_source.angle;
	tmp->len = tmp_source.len;
	tmp->ambience = tmp_source.ambience;
	tmp->diffuse = tmp_source.diffuse;
	tmp->specular = tmp_source.specular;
	tmp->phong_exp = tmp_source.phong_exp;
	tmp->smoothness = tmp_source.smoothness;
	tmp->transmittance = tmp_source.transmittance;
	tmp->refraction = tmp_source.refraction;
	tmp->emission_power = tmp_source.emission_power;
	tmp->specular_texture = tmp_source.specular_texture;
	tmp->texture_number = tmp_source.texture_number;
	tmp->texture_position = tmp_source.texture_position;
	tmp->coord_checker = tmp_source.coord_checker;
	tmp->material_checker = tmp_source.material_checker;
}
