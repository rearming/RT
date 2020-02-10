#include "rt.h"

/*
 * to do:
**	1. считать количество объектов, количество источников света, количество текстур, текстуры добавлять в отдельную структуру
**	2. добавить все возможные параметры объектов и источника света
 * 	3. уточнить где что проверяется
 * 	4. добавить в сцену
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

void		parse_json_file(json_t *root, t_tmp *tmp)
{
	void		*iter;
	const char	*key;
	json_t		*value;
	int			check;

	iter = json_object_iter(root);
	check = 0;
	while (iter)
	{
		key = json_object_iter_key(iter);
		value = json_object_iter_value(iter);
		if (json_is_object(value))
			check = parse_object(tmp, key, value);
		else if (json_is_array(value))
			check = parse_array(tmp, key, value);
		else if (json_is_number(value))
			check = parse_variable(tmp, key, value);
		else
			rt_raise_error(ERR_PARSING_WRONG_PARAM);
		if (check == -1)
			rt_raise_error(ERR_PARSING_WRONG_PARAM);
		while (tmp->next != NULL)
			tmp = tmp->next;
		iter = json_object_iter_next(root, iter);
	}
}

t_scene		rt_parse_scene(const char *json_scene_file)
{
	t_scene			scene;
	char			*text;
	t_tmp			*tmp;
	json_t			*root;
	json_error_t	error;

	if (!(tmp = (t_tmp *)malloc(sizeof(t_tmp))))
		rt_raise_error(ERR_MALLOC);
	text = read_file(json_scene_file, 10);
	init_tmp(tmp);
	root = json_loads(text, 0, &error);
	parse_json_file(root, tmp);
	add_elements(&scene, tmp);
	printff(tmp);
	json_decref(root);
	free(text);
	//scene = get_hardcoded_scene();
	//rt_correct_scene(&scene);
	return (scene);
}
