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
#include "rt_window_params.h"

static void add_rotation_matrix(t_tmp *tmp, t_object *object){
	int check_rotation;

	check_rotation = (tmp->checker[ALFA_ANGLE]) ? 1 : 0;
	check_rotation += (tmp->checker[BETA_ANGLE]) ? 1 : 0;
	check_rotation += (tmp->checker[GAMMA_ANGLE]) ? 1 : 0;
	if (check_rotation == 3 || check_rotation == 0)
	{
		count_matrix(object->rotation_matrix_T,
				(cl_float3) {{tmp->alfa_angle, tmp->beta_angle,
						 tmp->gamma_angle}}, true);
		count_matrix(object->reverse_rotation_matrix_T,
				(cl_float3) {{tmp->alfa_angle, tmp->beta_angle,
						 tmp->gamma_angle}}, false);
	}
	else if (check_rotation != 0)
		rt_raise_error(ERR_PARSING_MATRIX);
}

static void	add_objects(t_tmp *tmp, t_object *object)
{
	if (tmp->type == ELLIPSOID && tmp->distance == tmp->radius) {
		tmp->type = SPHERE;
		tmp->checker[DISTANCE] = false;
		printf("Ellipsoid changed to sphere with radius = r");
	}
//	check_object(tmp);
	object->type = tmp->type;
	object->normal = rt_vec_normalize(tmp->normal);
	object->center = tmp->center;
	object->distance = tmp->distance;
	object->axis = rt_vec_normalize(tmp->axis);
	object->vmax = tmp->vmax;
	object->vmin = tmp->vmin;
	object->radius = tmp->radius;
	object->radius_2 = tmp->radius_2;
	object->radius_ring = tmp->radius_ring;
	object->angle = tmp->angle;
	object->len = tmp->len;
	object->size = tmp->size;
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
	object->material.texture_pbr = tmp->texture_pbr;
	object->material.texture_number = tmp->texture_number;
	object->material.texture_normal = tmp->texture_normal;
	object->material.texture_pbr_index = tmp->texture_pbr_index;
	object->material.texture_position = tmp->texture_position;
	object->complicated_type = tmp->complicated;
	object->complicated_index = tmp->complicated_index;
	object->param_1 = tmp->param_1;
	object->param_0 = tmp->param_0;
	add_rotation_matrix(tmp, object);
}

static void	add_cam_and_light(t_camera *camera, t_light *light, t_tmp *tmp,
		bool cam)
{
	(cam) ? check_camera_or_light(tmp, true) :
		check_camera_or_light(tmp, false);
	if (cam)
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

static void	add_render_and_scene(t_scene *scene, t_tmp *tmp_iterator,
		bool render)
{
	if (render)
	{
		scene->clInfo.max_depth_raytrace = tmp_iterator->max_depth_r;
		scene->clInfo.max_depth_pathtrace = tmp_iterator->max_depth_p;
		scene->obj_file = (tmp_iterator->file != NULL) ?
			ft_strdup(tmp_iterator->file) : NULL;
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

static void	init_params(t_scene *scene, int *i_light, int *i_obj)
{
	*i_light = 0;
	*i_obj = 0;
	scene->objects = scene->obj_nbr > 0 ?
			rt_safe_malloc(sizeof(t_object) * scene->obj_nbr) : NULL;
	scene->lights = scene->lights_nbr > 0 ?
			rt_safe_malloc(sizeof(t_light) * scene->lights_nbr) : NULL;
}

void		add_elements(t_scene *scene, t_tmp *tmp)
{
	t_tmp	*tmp_iter;
	int		i_light;
	int		i_obj;

	init_params(scene, &i_light, &i_obj);
	tmp_iter = tmp;
	while (tmp_iter)
	{
		if (tmp_iter->struct_type == OBJECT && i_obj < scene->obj_nbr)
			add_objects(tmp_iter, &scene->objects[i_obj++]);
		else if (tmp_iter->struct_type == LIGHT && i_light < scene->lights_nbr)
			add_cam_and_light(NULL, &scene->lights[i_light++], tmp_iter, false);
		else if (tmp_iter->struct_type == CAMERA)
			add_cam_and_light(&scene->camera, NULL, tmp_iter, true);
		else if (tmp_iter->struct_type == RENDER_PARAMS)
			add_render_and_scene(scene, tmp_iter, true);
		else if (tmp_iter->struct_type == SCENE_PARAMS)
			add_render_and_scene(scene, tmp_iter, false);
		else
			rt_raise_error(ft_strjoin(ERR_PARSING_WRONG_PARAM, "unknown structure"));
		tmp_iter = tmp_iter->next;
	}
//	free_tmp(tmp);
}
