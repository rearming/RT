#include "rt.h"

/*
**	TODO do parsing gfoote
*/

void		printff(t_tmp *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		printf(" i = %i structure_type = %i type = %i %i\n",
			   i, tmp->structure_type, tmp->type, tmp->checker);
		i++;
		tmp = tmp->next;
	}
}

t_scene		rt_parse_scene(const char *json_scene_file)
{
//	t_scene		scene;
	char		*text;
	t_tmp			*tmp;
	json_t			*root;
	json_error_t	error;

	if (!(tmp = (t_tmp *)malloc(sizeof(t_tmp))))
		rt_raise_error(ERR_MALLOC);
	text = read_file(json_scene_file, 10);
	init_tmp(tmp);
	root = json_loads(text, 0, &error);
	parse_elem(root, tmp);
	printff(tmp);
	json_decref(root);
	free(text);
	//scene = get_hardcoded_scene();
	//rt_correct_scene(&scene);
	//return (scene);
}
