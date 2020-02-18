#include "rt.h"

/*
 * to do:
+*	1. считать количество объектов, количество источников света,
 	количество текстур, текстуры добавлять в отдельную структуру
 *	2. добавить все возможные параметры объектов и источника света
+* 	3. считать количество текстур и парсить их в отдельные листы
+* 	3. уточнить где что проверяется
+* 	4. добавить в сцену
+*	5. корректно чистить tmp
+*	6. выводить ошибки
 *	7. проверить считывание цвета (если флоты/инты)
 *	8. считывать opencl параметы
 *	9. добавить чекер
*/
char		*read_file(const char *argv, int buff_size)
{
	int		ret;
	char	buf[buff_size];
	char	*tmp;
	char	*result;
	int		fd;

	if (!(fd = open(argv, O_RDONLY)))
		rt_raise_error(ERR_INV_FILE);
	if (fd < 0 || !(result = ft_strnew(1)))
		rt_raise_error(ERR_INV_FILE);
	while ((ret = read(fd, buf, buff_size)) > 0 && result)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(result, buf);
		free(result);
		if (!tmp)
			rt_raise_error(ERR_MALLOC);
		result = tmp;
	}
	return (result);
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
	//print_tmp(tmp);
	add_elements(&scene, tmp);
	//print_textures();
	json_decref(root);
	free(text);
	//scene = get_hardcoded_scene();
	//rt_correct_scene(&scene);
	return (scene);
}
