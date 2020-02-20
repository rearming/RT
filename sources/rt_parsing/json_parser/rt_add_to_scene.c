#include "rt.h"
#include "rt_math_utils.h"

static void	add_to_objects(t_tmp *tmp, t_object *object)
{
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
	object->material.emission_color = tmp->color;
	object->material.emission_power = tmp->emission_power;
	object->material.specular_texture = tmp->specular_texture;
	object->material.texture_number = tmp->texture_number;
	object->material.texture_position = tmp->texture_position;
}

static void	add_camera(t_camera *camera, t_tmp *tmp)
{
	camera->pos = tmp->pos;
	camera->rotation = tmp->rotation;
	camera->viewport_distance = 1;
	camera->viewport_width = WIN_RATIO < 1 ? D_I_MAZOHIN : 1;
	camera->viewport_height = WIN_RATIO > 1 ? D_E_KARMATSKIY : 1 ;
}

static void	add_light(t_tmp *tmp, t_light *light)
{
	light->type = tmp->type;
	light->intensity = tmp->intensity;
	light->color = tmp->color;
	light->pos = tmp->pos;
	light->dir = tmp->dir;
}

static void	free_tmp(t_tmp *tmp)
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

void		add_elements(t_scene *scene, t_tmp *tmp)
{
	t_tmp	*tmp_iterator;
	int		i_light;
	int		i_object;

	i_light = 0;
	i_object = 0;
	tmp_iterator = tmp;
	scene->objects = rt_safe_malloc(sizeof(t_object) * scene->obj_nbr);
	scene->lights = rt_safe_malloc(sizeof(t_light) * scene->lights_nbr);
	scene->camera = (t_camera){};
	while (tmp_iterator)
	{
		if (tmp_iterator->structure_type == OBJECT)
			add_to_objects(tmp_iterator, &scene->objects[i_object++]);
		else if (tmp_iterator->structure_type == CAMERA)
			add_camera(&scene->camera, tmp_iterator);
		else if (tmp_iterator->structure_type == LIGHT)
			add_light(tmp_iterator, &scene->lights[i_light++]);
		else if (tmp_iterator->structure_type == RENDER_PARAMETERS)
			printf("render parameters added\n");//continue;
		else if (tmp_iterator->structure_type == SCENE_PARAMETERS)
			printf("where should I add scene parameters?\n");
		else
			rt_raise_error(ERR_PARSING_WRONG_TYPE);
		tmp_iterator = tmp_iterator->next;
	}
	free_tmp(tmp);
}
