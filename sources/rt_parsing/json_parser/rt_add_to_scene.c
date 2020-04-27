/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_add_to_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:45:25 by gfoote            #+#    #+#             */
/*   Updated: 2020/03/10 16:45:27 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_parsing.h"
#include "rt_math_utils.h"
static void add_rotation_matrix(t_tmp *tmp, t_object *object){
	int check_rotation;

	check_rotation = (tmp->checker[ALFA_ANGLE]) ? 1 : 0;
	check_rotation += (tmp->checker[BETA_ANGLE]) ? 1 : 0;
	check_rotation += (tmp->checker[GAMMA_ANGLE]) ? 1 : 0;
	check_rotation += (tmp->checker[reverse_ALFA_ANGLE]) ? 10 : 0;
	check_rotation += (tmp->checker[reverse_BETA_ANGLE]) ? 10 : 0;
	check_rotation += (tmp->checker[reverse_GAMMA_ANGLE]) ? 10 : 0;
	if (check_rotation == 30) {
		object->reverse_rotation_matrix_T;
	} else if (check_rotation == 3) {
		object->rotation_matrix_T;
	} else if (check_rotation != 0){
		rt_raise_error(ERR_PARSING_MATRIX);
	}
}

static void	add_objects(t_tmp *tmp, t_object *object)
{
	if (tmp->type == ELLIPSOID && tmp->distance == tmp->radius) {
		tmp->type = SPHERE;
		tmp->checker[DISTANCE] = false;
		printf("Ellipsoid changed to sphere with radius = r");
	}
	check_object(tmp);
	object->type = tmp->type;
	object->normal = vec_normalize(tmp->normal);
	object->center = tmp->center;
	object->distance = tmp->distance;
	object->axis = vec_normalize(tmp->axis);
	object->vmax = tmp->vmax;
	object->vmin = tmp->vmin;
	object->radius = tmp->radius;
	object->angle = tmp->angle;
	object->len = tmp->len;
	object->material.ambient = tmp->ambience;
	object->material.diffuse = tmp->diffuse;
	object->material.specular = tmp->specular;
	object->material.phong_exp = tmp->phong_exp;
	object->material.smoothness = tmp->smoothness;
	object->material.transmittance = tmp->transmittance;
	object->material.refraction = tmp->refraction;
	object->material.emission_color = tmp->emission_color;
	object->material.emission_power = tmp->emission_power;
	object->material.specular_texture = tmp->specular_texture;
	object->material.texture_number = tmp->texture_number;
	object->material.texture_position = tmp->texture_position;
	object->complicated_type = tmp->complicated;
	object->comlicated_index = tmp->complicated_index;
	add_rotation_matrix(tmp, object);
	//change alpha, betta, gamma to float3[3] rotation_matrix_T;
	// float3[3] reverse_rotation_matrix_T; характеристики объектов
	// object->complicated = nothing, union, different, intersection +
	// object->complicated_index +;
}

static void	add_cam_and_light(t_camera *camera, t_light *light, t_tmp *tmp,
		bool cam)
{
	(cam) ? check_camera_or_light(tmp, true) : check_camera_or_light(tmp, false);
	if (cam)
	{
		camera->pos = tmp->pos;
		camera->rotation = tmp->rotation;
		camera->viewport_distance = 1;
		camera->viewport_width = WIN_RATIO;
		camera->viewport_height = 1;
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

static void	add_render_and_scene(t_scene *scene, t_tmp *tmp_iterator,
		bool render)
{
	if (render)
	{
		scene->clInfo.max_depth_raytrace = tmp_iterator->max_depth_r;
		scene->clInfo.max_depth_pathtrace = tmp_iterator->max_depth_p;
		scene->obj_file = (tmp_iterator->file != NULL) ? ft_strdup(tmp_iterator->file) : NULL;
		free(tmp_iterator->file);
	}
	else
	{
		if (tmp_iterator->checker[GAMMA] + tmp_iterator->checker[EXPOSURE] != 2)
			rt_raise_error(ERR_PARSING_WRONG_SCENE_PARAMS);
		scene->clInfo.gamma = tmp_iterator->gamma;
		scene->clInfo.exposure = tmp_iterator->exposure;
	}
}

void		add_elements(t_scene *scene, t_tmp *tmp)
{
	t_tmp	*tmp_iter;
	int		i_light;
	int		i_obj;

	i_light = 0;
	i_obj = 0;
	tmp_iter = tmp;
	scene->objects = scene->obj_nbr > 0 ?
		rt_safe_malloc(sizeof(t_object) * scene->obj_nbr) : NULL;
	scene->lights = scene->lights_nbr > 0 ?
		rt_safe_malloc(sizeof(t_light) * scene->lights_nbr) : NULL;
	while (tmp_iter)
	{
		if (tmp_iter->structure_type == OBJECT && i_obj < scene->obj_nbr)
			add_objects(tmp_iter, &scene->objects[i_obj++]);
		else if (tmp_iter->structure_type == LIGHT && i_light < scene->lights_nbr)
			add_cam_and_light(NULL, &scene->lights[i_light++], tmp_iter, false);
		else if (tmp_iter->structure_type == CAMERA)
			add_cam_and_light(&scene->camera, NULL, tmp_iter, true);
		else if (tmp_iter->structure_type == RENDER_PARAMS)
			add_render_and_scene(scene, tmp_iter, true);
		else if (tmp_iter->structure_type == SCENE_PARAMS)
			add_render_and_scene(scene, tmp_iter, false);
		else
			rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_PARAM,
					"unknown structure"));
		tmp_iter = tmp_iter->next;
	}
	free_tmp(tmp);
}
