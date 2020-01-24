#include "rt.h"

static inline void		correct_lights_intensity(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < scene->lights_nbr)
	{
		scene->lights[i].intensity /= scene->lights_nbr;
		i++;
	}
}

static inline void		correct_specular(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < scene->obj_nbr)
	{
		if (scene->objects[i].material.specular == 0)
			scene->objects[i].material.specular = 0.00001;
	}
}

void		rt_correct_scene(t_scene *scene)
{
//	correct_lights_intensity(scene);
}
