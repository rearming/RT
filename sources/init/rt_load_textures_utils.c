/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_load_textures_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			init_basic_textures_parameters(void)
{
	g_textures.texture_list_size = 0;
	g_textures.texture_list = NULL;
	g_textures.texture_info = (t_texture_info *)rt_safe_malloc(
			g_textures.texture_info_size * sizeof(t_texture_info));
	return (-1);
}

void		rt_add_start_position(int i)
{
	if (i < (int)g_textures.texture_info_size && i > 0)
		g_textures.texture_info[i].start = g_textures.texture_info[i - 1].start
		+ g_textures.texture_info[i - 1].width
		* g_textures.texture_info[i - 1].height;
	else
		g_textures.texture_info[i].start = 0;
}

static int	exists(const char *file_name)
{
	FILE *file;

	if ((file = fopen(file_name, "r")))
	{
		fclose(file);
		return (1);
	}
	return (0);
}

char		*found_file(const char *file, char **folders_names)
{
	int		i;
	char	*check;

	i = 0;
	if (exists(file))
		return (ft_strdup(file));
	else if (exists(check = ft_strjoin(TEXTURES_FOLDER, file)))
		return (check);
	else if (folders_names)
	{
		while (folders_names[i] != NULL)
		{
			ft_strclr(check);
			free(check);
			if (exists(check = ft_strjoin(g_textures.folders_names[i], file)))
				return (check);
			i++;
		}
	}
	ft_strclr(check);
	free(check);
	return (NULL);
}

void		bzero_g_textures(void)
{
	g_textures.texture_list_size = 0;
	g_textures.texture_info_size = 0;
	g_textures.folders_names = NULL;
	g_textures.textures_names = NULL;
	g_textures.texture_list = NULL;
	g_textures.skybox_list = NULL;
	g_textures.skybox_info = NULL;
}
