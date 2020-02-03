#include "rt.h"

static int 	add_to_objects()
{

}

static int 	add_camera(t_camera *camera, t_tmp *tmp)
{
	camera->pos = tmp->pos;
	camera->rotation = tmp->rotation;
	return (CAMERA);
}

static int 	add_light()
{

}

void	add_elements(t_scene *scene, t_tmp *tmp)
{
	t_tmp	*tmp_iterator;
	int		checker;

	tmp_iterator = tmp;
	checker = 0;
	while(tmp_iterator)
	{
		//if (tmp_iterator->structure_type == OBJECT)
			checker += add_to_objects();
		if (tmp_iterator->structure_type == CAMERA)
			checker += add_camera(&scene->camera, tmp);
		//else if (tmp_iterator->structure_type == LIGHT)
		//	checker += add_light();
		else
			rt_raise_error(-1);
		if (checker == -1)
			rt_raise_error(ERR_PARSING_WRONG_PARAM);
		tmp_iterator = tmp_iterator->next;
	}
	free(tmp);
	if (checker != CAMERA) //if no camera or no light or no object;
		rt_raise_error(ERR_PARSING_WRONG_PARAM);
}