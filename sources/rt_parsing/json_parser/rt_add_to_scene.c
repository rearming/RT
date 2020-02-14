#include "rt.h"

static int	add_to_objects(t_tmp *tmp, t_object *object)
{
	object->type = tmp->type;
	object->center = tmp->pos;
	object->normal = tmp->normal;
	object->radius = tmp->radius;
	object->angle = tmp->angle;
	object->len = tmp->len;
	object->material.emission_color = tmp->color;
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
}

static int	add_light(t_tmp *tmp, t_light *light)
{
	light->type = tmp->type;
	light->intensity = tmp->intensity;
	light->color = tmp->color;
	if (tmp->coord_checker % 10 == 1)
		light->pos = tmp->pos;
	if (tmp->coord_checker / DIRECTION % 10 == 1)
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
	while (tmp_iterator)
	{
		if (tmp_iterator->structure_type == OBJECT)
			add_to_objects(tmp_iterator, &scene->objects[i_object++]);
		else if (tmp_iterator->structure_type == CAMERA)
			add_camera(&scene->camera, tmp);
		else if (tmp_iterator->structure_type == LIGHT)
			add_light(tmp_iterator, &scene->lights[i_light++]);
		else
			rt_raise_error("check the type, it's not object/light/camera");
		tmp_iterator = tmp_iterator->next;
	}
	free_tmp(tmp);
}
