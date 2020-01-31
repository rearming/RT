#include "rt.h"

void	init_basic_textures_parameters(void)
{
	g_textures.texture_list = NULL;
	g_textures.texture_info_size = 0;
	g_textures.texture_list_size = 0;
}

//printf("texture name: %s texture number: [%i], width: [%i], heigth: [%i], bpp: [%i], size: [%lu]\n",
//	   entry->d_name, i, g_textures.texture_info[i].width, g_textures.texture_info[i].height,
//	   g_textures.texture_info[i].bpp, ft_strlen((const char*)tmp_texture));