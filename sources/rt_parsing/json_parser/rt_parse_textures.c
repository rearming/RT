#include "rt.h"
//проверять если длинна больше длинны официальной папки, то сверять в сцепке с основной папки иначе просто
t_texture_name	*ft_new_texture_name(const char *data)
{
	t_texture_name *tmp;

	tmp = (t_texture_name *)rt_safe_malloc(sizeof(t_texture_name));
	if (tmp)
	{
		tmp->name = ft_strdup(data);
		tmp->next = NULL;
	}
	return (tmp);
}

int			ft_add_texture_name_back(t_texture_name **list, const char *data)
{
	t_texture_name *tmp;
	int num = 0;

	if (!(*list))
		*list = ft_new_texture_name(data);
	else
	{
		tmp = *list;
		while(tmp->next)
		{
			num++;
			tmp = tmp->next;
		}
		num++;
		tmp->next = ft_new_texture_name(data);
	}
	return (num);
}


int		search(const char *name)//запустить t_list c функцией equal
{
	t_texture_name *iter;
	int num;

	num = -1;
	iter = g_textures.textures_names;
	while(iter)
	{
		num++;
		if (ft_strequ(name, iter->name))
			return (num);
		iter = iter->next;
	}
	return (-1);
}

int 	parse_texture(const char *name)
{
	int num;

	num = search(name);
	if (num != -1)
		return (num);
	else
		num = ft_add_texture_name_back(&g_textures.textures_names, name);
	return (num);
}