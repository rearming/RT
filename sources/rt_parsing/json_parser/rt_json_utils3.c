/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_json_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:48:00 by gfoote            #+#    #+#             */
/*   Updated: 2020/03/10 16:48:02 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_parsing.h"
#include "rt_math_utils.h"
#include "rt_window_params.h"

void		check_duplicated(bool *checker, int number)
{
	if (checker[number] == true)
		rt_raise_error(ERR_PARSING_DUPLICATED_PARAM);
	else
		checker[number] = true;
}

static void	count_matrix(cl_float3 *rotation_matrix, cl_float3 angle,
		bool reversed)
{
	cl_float3 c;
	cl_float3 s;

	c = (cl_float3){{cos(angle.x), cos(angle.y), cos(angle.z)}};
	s = (cl_float3){{sin(angle.x), sin(angle.y), sin(angle.z)}};
	s = reversed ? (cl_float3){{-s.x, -s.y, -s.z}} : s;
	rotation_matrix[0] = (cl_float3){{c.x * c.z - s.x * c.y * s.z,
			-c.x * s.z - s.x * c.y * c.z, s.x * s.y}};
	rotation_matrix[1] = (cl_float3){{s.x * c.z + c.x * c.y * s.z,
			-s.x * s.z + c.x * c.y * c.z, -c.x * s.y}};
	rotation_matrix[2] = (cl_float3){{s.y * s.z, s.y * c.z, c.y}};
}

void		add_rotation_matrix(t_tmp *tmp, t_object *object)
{
	int check_rotation;

	check_rotation = (tmp->checker[ALFA_ANGLE]) ? 1 : 0;
	check_rotation += (tmp->checker[BETA_ANGLE]) ? 1 : 0;
	check_rotation += (tmp->checker[GAMMA_ANGLE]) ? 1 : 0;
	if (check_rotation == 3 || check_rotation == 0)
	{
		count_matrix(object->rotation_matrix_t,
			(cl_float3) {{tmp->alfa_angle,
				tmp->beta_angle, tmp->gamma_angle}}, true);
		count_matrix(object->reverse_rotation_matrix_t,
				(cl_float3) {{tmp->alfa_angle, tmp->beta_angle,
				tmp->gamma_angle}}, false);
	}
	else if (check_rotation != 0)
		rt_raise_error(ERR_PARSING_MATRIX);
}

void		add_cam_and_light(t_camera *camera, t_light *light, t_tmp *tmp)
{
	check_camera_or_light(tmp->checker, tmp->type, tmp->struct_type);
	if (tmp->struct_type == CAMERA)
	{
		camera->pos = tmp->pos;
		camera->rotation = tmp->rotation;
		camera->viewport_distance = 1;
		camera->viewport_width = WIN_RATIO;
		camera->viewport_height = 1;
		camera->focal_distance = 7;
		camera->aperture = 0.5f;
		camera->blur_strength = 1.5f;
	}
	else
	{
		light->type = tmp->type;
		light->intensity = tmp->intensity;
		light->color = tmp->color;
		light->pos = tmp->pos;
		light->dir = tmp->dir;
	}
}

void		free_tmp(t_tmp *tmp)
{
	t_tmp	*tmp_iterator;

	while (tmp)
	{
		tmp_iterator = tmp->next;
		free(tmp);
		tmp = tmp_iterator;
	}
	free(tmp);
}
