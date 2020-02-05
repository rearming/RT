#include "rt.h"

int	init_basic_textures_parameters(void)
{
	g_textures.texture_info_size = 0;
	g_textures.texture_list_size = 0;
	g_textures.texture_list = NULL;
	return (0);
}

void	init_final_texture_parameters(size_t list_size)
{
	g_textures.texture_info_size = TEXTURE_NUM;
	g_textures.texture_list_size = list_size;
}

void	rt_add_start_position(int i)
{
	if (i < TEXTURE_NUM && i > 0)
		g_textures.texture_info[i].start = g_textures.texture_info[i - 1].start
										   + g_textures.texture_info[i - 1].width
											 * g_textures.texture_info[i - 1].height;
	else
		g_textures.texture_info[i].start = 0;
}

