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

void		init_textures_default(void)
{
	g_textures.textures_names = NULL;
	g_textures.skybox_info = rt_safe_malloc(sizeof(t_skybox_info));
	g_textures.texture_info_size = 0;
	g_textures.skybox_info->skybox_exist = false;
}

static void	init_tmp_material(t_tmp *tmp)
{
	tmp->ambience = (cl_float3){{0, 0, 0}};
	tmp->diffuse = (cl_float3){{0, 0, 0}};
	tmp->specular = (cl_float3){{0, 0, 0}};
	tmp->phong_exp = 0;
	tmp->smoothness = 0;
	tmp->transmittance = 0;
	tmp->refraction = 1;
	tmp->emission_color = (cl_float3){{0, 0, 0}};
	tmp->emission_power = 0;
	tmp->specular_texture = 0;
	tmp->texture_number = NOT_SET;
	tmp->texture_position = (cl_float3){{0, 0, 0}};
}

static void init_tmp_complicated_params(t_tmp *tmp)
{
	tmp->complicated = (int)NULL;
	tmp->complicated_index = NOT_SET;
	tmp->alfa_angle = 0;
	tmp->beta_angle = 0;
	tmp->gamma_angle = 0;
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
	tmp->max_depth_r = 8;
	tmp->max_depth_p = 8;
	tmp->skybox_num = NOT_SET;
	tmp->exposure = NOT_SET;
	tmp->gamma = NOT_SET;
	tmp->file = NULL;
	init_tmp_material(tmp);
	init_tmp_complicated_params(tmp);
	ft_bzero(&tmp->checker, sizeof(tmp->checker) / sizeof(bool));
}

void		count_elements(t_scene *scene, t_tmp *tmp)
{
	t_tmp	*tmp_iter;
	int		check_param;
	t_name	*texture_iter;

	texture_iter = g_textures.textures_names;
	tmp_iter = tmp;
	scene->lights_nbr = 0;
	scene->obj_nbr = 0;
	check_param = 0;
	while (tmp_iter)
	{
		scene->lights_nbr += (tmp_iter->structure_type == LIGHT) ? 1 : 0;
		scene->obj_nbr += (tmp_iter->structure_type == OBJECT) ? 1 : 0;
		check_param += (tmp_iter->structure_type == CAMERA) ? 1 : 0;
		check_param += (tmp_iter->structure_type == RENDER_PARAMS) ? 10 : 0;
		check_param += (tmp_iter->structure_type == SCENE_PARAMS) ? 100 : 0;
		tmp_iter = tmp_iter->next;
	}
	while (texture_iter)
	{
		g_textures.texture_info_size++;
		texture_iter = texture_iter->next;
	}
	if (check_param != 111)
		rt_raise_error(ERR_PARSING_SCENE_NOT_SPECIFIED);
}

void	count_matrix(cl_float3 *rotation_matrix, cl_float3 *rotation_matrix_,
		cl_float3 angle, bool reversed) {

	cl_float3 c = (cl_float3){{cos(angle.x), cos(angle.y), cos(angle.z)}};
	cl_float3 s = (cl_float3){{sin(angle.x), sin(angle.y), sin(angle.z)}};
	s = reversed ? (cl_float3){{-s.x, -s.y, -s.z}} : s;

	rotation_matrix[0] = (cl_float3){{c.x * c.z - s.x * c.y * s.z,
								   -c.x * s.z - s.x * c.y *c.z,
								   s.x *s.y}};
	rotation_matrix[1] = (cl_float3){{s.x * c.z + c.x * c.y * s.z,
								   -s.x * s.z + c.x * c.y * c.z,
								   -s.y * c.z}};
	rotation_matrix[2] = (cl_float3){{s.y * s.z,
								   s.y * c.z,
								   c.y}};
}