#include "rt.h"

/*
 * to do:
**	1. считать количество объектов, количество источников света, количество текстур, текстуры добавлять в отдельную структуру
**	2. добавить все возможные параметры объектов и источника света
 * 	3. считать количество текстур и парсить их в однельные листы
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
			   i, tmp->structure_type, tmp->type, tmp->coord_checker);
		i++;
		tmp = tmp->next;
	}
}

void 		count_elements(t_scene *scene, t_tmp *tmp)
{
	t_tmp	*tmp_iterator;
	int		check_camera;

	check_camera = 0;
	tmp_iterator = tmp;
	scene->lights_nbr = 0;
	scene->obj_nbr = 0;
	while(tmp_iterator)
	{
		if (tmp_iterator->structure_type == LIGHT)
			scene->lights_nbr++;
		else if (tmp_iterator->structure_type == OBJECT)
			scene->obj_nbr++;
		if (tmp_iterator->structure_type == CAMERA)
			check_camera++;
		tmp_iterator = tmp_iterator->next;
	}
	if (check_camera != 1)
		rt_raise_error("wrong camera");
}

void		parse_json_file(json_t *root, t_tmp *tmp)
{
	void		*iter;
	const char	*key;
	json_t		*value;

	iter = json_object_iter(root);
	while (iter)
	{
		key = json_object_iter_key(iter);
		value = json_object_iter_value(iter);
		if (json_is_object(value))
			parse_object(tmp, key, value);
		else if (json_is_array(value))
			parse_array(tmp, key, value);
		else if (json_is_number(value))
			parse_variable(tmp, key, value);
		else if (json_is_string(value))
			parse_string(tmp, key, value);
		else
			rt_raise_error(ERR_PARSING_WRONG_PARAM);
		while (tmp->next != NULL)
			tmp = tmp->next;
		iter = json_object_iter_next(root, iter);
		printf("%s\n", key);
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
	count_elements(&scene, tmp);
	add_elements(&scene, tmp);
	printff(tmp);
	json_decref(root);
	free(text);
	//scene = get_hardcoded_scene();
	//rt_correct_scene(&scene);
	return (scene);
}
