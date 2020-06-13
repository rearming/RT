/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_name		*ft_new_texture_name(const char *data)
{
	t_name *tmp;

	tmp = rt_safe_malloc(sizeof(t_name));
	tmp->name = ft_strdup((char *)data);
	tmp->next = NULL;
	ft_strclr((char *)data);
	return (tmp);
}

int			ft_add_texture_name_back(t_name **list,
											const char *data)
{
	t_name	*tmp;
	int		num;

	num = 0;
	if (!*list)
		*list = ft_new_texture_name(data);
	else
	{
		tmp = *list;
		while (tmp->next)
		{
			num++;
			tmp = tmp->next;
		}
		num++;
		tmp->next = ft_new_texture_name(data);
	}
	return (num);
}

static int	search(const char *name)
{
	t_name	*iter;
	int		num;

	num = -1;
	iter = g_textures.textures_names;
	while (iter)
	{
		num++;
		if (ft_strequ(name, iter->name))
			return (num);
		iter = iter->next;
	}
	return (-1);
}

int			parse_texture(const char *name)
{
	int num;

	num = search(name);
	if (num != -1)
		return (num);
	else
		num = ft_add_texture_name_back(&g_textures.textures_names, name);
	return (num);
}

void		add_directory(json_t *value)
{
	size_t i;
	size_t array_size;

	i = 0;
	array_size = json_array_size(value);
	g_textures.folders_names = rt_safe_malloc(array_size);
	while (i < array_size)
	{
		g_textures.folders_names[i] =
				ft_strdup(json_string_value(json_array_get(value, i)));
		i++;
	}
	g_textures.folders_names[i] = NULL;
}
