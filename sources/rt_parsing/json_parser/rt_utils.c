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

static void	init_tmp_material(t_tmp *tmp)
{
	tmp->ambience = (cl_float3){{0, 0, 0}};
	tmp->diffuse = (cl_float3){{0, 0, 0}};
	tmp->specular = (cl_float3){{0, 0, 0}};
	tmp->phong_exp = 0;
	tmp->smoothness = 0;
	tmp->transmittance = 0;
	tmp->refraction = 0;
	tmp->emission_color = (cl_float3){{0, 0, 0}};
	tmp->emission_power = 0;
	tmp->specular_texture = 0;
	tmp->texture_number = NOT_SET;
	tmp->texture_position = (cl_float3){{0, 0, 0}};
}

void		init_tmp(t_tmp *tmp)
{
	tmp->next = NULL;
	tmp->structure_type = NOT_SET;
	tmp->type = NOT_SET;
	tmp->pos = (cl_float3){{0, 0, 0}};
	tmp->rotation = (cl_float3){{0, 0, 0}};
	tmp->intensity = NOT_SET;
	tmp->dir = (cl_float3){{0, 0, 0}};
	tmp->color = (cl_float3){{0, 0, 0}};
	tmp->normal = (cl_float3){{0, 1, 0}};
	tmp->axis = (cl_float3){{0, 1, 0}};
	tmp->center = (cl_float3){{0, 0, 0}};
	tmp->vmin = (cl_float3){{0, 0, 0}};
	tmp->vmax = (cl_float3){{0, 0, 0}};
	tmp->distance = NOT_SET;
	tmp->radius = NOT_SET;
	tmp->angle = NOT_SET;
	tmp->len = NOT_SET;
	init_tmp_material(tmp);
	ft_bzero(&tmp->checker, 28);
}

void		count_elements(t_scene *scene, t_tmp *tmp)
{
	t_tmp			*tmp_iterator;
	int				check_camera;
	t_texture_name	*texture_iter;

	texture_iter = g_textures.textures_names;
	tmp_iterator = tmp;
	scene->lights_nbr = 0;
	scene->obj_nbr = 0;
	g_textures.texture_info_size = 0;
	check_camera = 0;
	while (tmp_iterator)
	{
		scene->lights_nbr += (tmp_iterator->structure_type == LIGHT) ? 1 : 0;
		scene->obj_nbr += (tmp_iterator->structure_type == OBJECT) ? 1 : 0;
		check_camera += (tmp_iterator->structure_type == CAMERA) ? 1 : 0;
		tmp_iterator = tmp_iterator->next;
	}
	while (texture_iter)
	{
		g_textures.texture_info_size++;
		texture_iter = texture_iter->next;
	}
	if (check_camera != 1)
		rt_raise_error(ERR_PARSING_CAMERA);
}

void		check_duplicated(bool *checker, int number)
{
	if (checker[number] == true)
		rt_raise_error(ERR_PARSING_DUPLICATED_PARAM);
	else
		checker[number] = true;
}
