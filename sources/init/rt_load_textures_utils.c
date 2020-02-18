#include "rt.h"

int	init_basic_textures_parameters(void)
{
	g_textures.texture_list_size = 0;
	g_textures.texture_list = NULL;
	g_textures.texture_info = (t_texture_info *)rt_safe_malloc(
			g_textures.texture_info_size * sizeof(t_texture_info));
	return (0);
}

void	rt_add_start_position(int i)
{
	if (i < (int)g_textures.texture_info_size && i > 0)
		g_textures.texture_info[i].start = g_textures.texture_info[i - 1].start
		+ g_textures.texture_info[i - 1].width
		* g_textures.texture_info[i - 1].height;
	else
		g_textures.texture_info[i].start = 0;
}

