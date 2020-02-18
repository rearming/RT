#include "rt.h"

int				init_basic_textures_parameters(void)
{
	g_textures.texture_list_size = 0;
	g_textures.texture_list = NULL;
	g_textures.texture_info = (t_texture_info *)rt_safe_malloc(
			g_textures.texture_info_size * sizeof(t_texture_info));
	return (-1);
}

void			rt_add_start_position(int i)
{
	if (i < (int)g_textures.texture_info_size && i > 0)
		g_textures.texture_info[i].start = g_textures.texture_info[i - 1].start
		+ g_textures.texture_info[i - 1].width
		* g_textures.texture_info[i - 1].height;
	else
		g_textures.texture_info[i].start = 0;
}

t_texture_name	*ft_new_texture_name(char *data)
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

void			ft_add_texture_name_back(t_texture_name **list, char *data)
{
	t_texture_name *tmp;

	if (!(*list))
		*list = ft_new_texture_name(data);
	else
	{
		tmp = *list;
		while(tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = ft_new_texture_name(data);
	}
}