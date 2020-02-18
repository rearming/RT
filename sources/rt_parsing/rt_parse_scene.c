#include "rt.h"

/*
 * to do:
+*	1. считать количество объектов, количество источников света,
 	количество текстур, текстуры добавлять в отдельную структуру
+*	2. добавить все возможные параметры объектов и источника света
+* 	3. считать количество текстур и парсить их в однельные листы
+* 	3. уточнить где что проверяется
+* 	4. добавить в сцену


 проверить parse_string, add elements, add textures and add render parameters
*/

void	printff(t_tmp *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		printf(" i = %i structure_type = %i type = %i \n",
				i, tmp->structure_type, tmp->type);
		i++;
		tmp = tmp->next;
	}
}

void	parse_json_file(json_t *root, t_tmp *tmp)
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

void			print_textures(void)
{
	t_texture_name *tmp;
	tmp = g_textures.textures_names;
	while (tmp)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}

t_scene	rt_parse_scene(const char *json_scene_file)
{
	t_scene			scene;
	char			*text;
	t_tmp			*tmp;
	json_t			*root;
	json_error_t	error;

	tmp = rt_safe_malloc(sizeof(t_tmp));
	text = read_file(json_scene_file, 10);
	init_tmp(tmp);
	g_textures.textures_names = NULL;
	root = json_loads(text, 0, &error);
	parse_json_file(root, tmp);
	count_elements(&scene, tmp);
	add_elements(&scene, tmp);
	print_textures();
	//printff(tmp);
	json_decref(root);
	free(text);
	//scene = get_hardcoded_scene();
	//rt_correct_scene(&scene);
	return (scene);
}
