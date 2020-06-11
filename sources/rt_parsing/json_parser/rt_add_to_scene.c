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

static void	add_material(t_tmp *tmp, t_object *object)
{
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
	object->raymarch_type = (tmp->type <= ELLIPSOID) ? SIMPLE : tmp->raymarch;
	object->raymarch_index = tmp->raymarch_index;
	object->param_1 = tmp->param_1;
	object->param_0 = tmp->param_0;
}

static void	add_objects(t_tmp *tmp, t_object *object)
{
	if (tmp->type == ELLIPSOID && tmp->distance == tmp->radius)
	{
		tmp->type = SPHERE;
		tmp->checker[DISTANCE] = false;
		printf("Ellipsoid changed to sphere with radius = r");
	}
	check_object(tmp->checker, tmp->type, tmp->texture_pbr);
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
	add_material(tmp, object);
	add_rotation_matrix(tmp, object);
}

static void	add_render_and_scene(t_scene *scene, t_tmp *tmp_iterator,
		bool render)
{
	if (render)
	{
		scene->cl_info.max_depth_raytrace = tmp_iterator->max_depth_r;
		scene->cl_info.max_depth_pathtrace = tmp_iterator->max_depth_p;
		scene->obj_file = (tmp_iterator->file != NULL) ?
			ft_strdup(tmp_iterator->file) : NULL;
		free(tmp_iterator->file);
	}
	else
	{
		if (tmp_iterator->checker[GAMMA] + tmp_iterator->checker[EXPOSURE] != 2)
			rt_raise_error(ERR_PARSING_WRONG_SCENE_PARAMS);
		scene->cl_info.gamma = tmp_iterator->gamma;
		scene->cl_info.exposure = tmp_iterator->exposure;
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
			add_cam_and_light(NULL, &scene->lights[i_light++], tmp_iter);
		else if (tmp_iter->struct_type == CAMERA)
			add_cam_and_light(&scene->camera, NULL, tmp_iter);
		else if (tmp_iter->struct_type == RENDER_PARAMS)
			add_render_and_scene(scene, tmp_iter, true);
		else if (tmp_iter->struct_type == SCENE_PARAMS)
			add_render_and_scene(scene, tmp_iter, false);
		else
			rt_raise_error(ft_strjoin(ERR_PARS_WRONG_PRM, "unknown structure"));
		tmp_iter = tmp_iter->next;
	}
	free_tmp(tmp);
}
