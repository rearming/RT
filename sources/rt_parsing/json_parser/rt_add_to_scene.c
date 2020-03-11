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

static void	add_objects(t_tmp *tmp, t_object *object)
{
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
}

static void	add_cam_and_light(t_camera *camera, t_light *light, t_tmp *tmp,
		bool cam)
{
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
		scene->obj_file = ft_strdup(tmp_iterator->file);
		free(tmp_iterator->file);
	}
	else
	{
		scene->clInfo.gamma = tmp_iterator->gamma;
		scene->clInfo.exposure = tmp_iterator->exposure;
	}
}

static void	add_elements2(t_scene *scene, t_tmp *tmp_iterator)
{
	if (tmp_iterator->structure_type == CAMERA)
		add_cam_and_light(&scene->camera, NULL, tmp_iterator, true);
	else if (tmp_iterator->structure_type == RENDER_PARAMS)
		add_render_and_scene(scene, tmp_iterator, true);
	else
		add_render_and_scene(scene, tmp_iterator, false);
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
		else if (tmp_iter->structure_type == CAMERA || tmp_iter->structure_type
			== RENDER_PARAMS || tmp_iter->structure_type == SCENE_PARAMS)
			add_elements2(scene, tmp_iter);
		else
			rt_raise_error(ERR_PARSING_WRONG_TYPE);
		tmp_iter = tmp_iter->next;
	}
	free_tmp(tmp);
}
