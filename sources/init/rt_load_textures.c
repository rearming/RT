#include "rt.h"
#include "stb_image.h"
# include <dirent.h>

unsigned long ft_strlen2(u_char *list)
{
	int i = 0;
	while(list[i])
	{
		i++;
	}
	return (i);
}


void	rt_textures_init(void)
{
	int i;
	DIR *dir;
	struct dirent *entry;
	char *tmp_filename;
	stbi_uc *tmp_texture;


	g_sdl.texture_info = rt_safe_malloc(TEXTURE_NUM * sizeof(t_texture_info));
	if (!g_sdl.texture_info)
		return(rt_raise_error(ERR_MALLOC));
	dir = opendir("textures/2sphere/");
	if (!dir)
		return(rt_raise_error(ERR_INVALID_TEXRTURE_DIR));
	i = 0;
	g_sdl.texture_info[0].start = 0;
	//g_sdl.texture_list = (u_char *)malloc(sizeof(u_char)*1);
	g_sdl.texture_list = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		if (!(tmp_filename = ft_strjoin("textures/2sphere/", entry->d_name)))
			exit(-1);
		tmp_texture = stbi_load(tmp_filename, &g_sdl.texture_info[i].width, &g_sdl.texture_info[i].height, &g_sdl.texture_info[i].bpp, 0);
		printf("%i texture %lu\n", i, ft_strlen2(tmp_texture));
		g_sdl.texture_list = ft_strjoin((const char*)g_sdl.texture_list, (const char *)tmp_texture);
		if (i + 1 < TEXTURE_NUM)
			g_sdl.texture_info[i+1].start = g_sdl.texture_info[i].start + g_sdl.texture_info[i].width * g_sdl.texture_info[i].height + 1;
		free(tmp_filename);
		free(tmp_texture);
		printf("%i texture %lu\n", i, ft_strlen2(g_sdl.texture_list));
		if (g_sdl.texture_list == NULL)
			return (rt_raise_error(ERR_SDL_TEXTURE_CREATE));
		printf("%i %s width = %i height = %i, start = %i\n", i, entry->d_name, g_sdl.texture_info[i].width, g_sdl.texture_info[i].height, g_sdl.texture_info[i].start);
		i++;
	}
	printf("texture %lu\n", ft_strlen2(g_sdl.texture_list));
	int z = 0;
	/*while (z < TEXTURE_NUM)
	{
		printf("%i width = %i height = %i, start = %i\n", z, g_sdl.texture_info[z].width, g_sdl.texture_info[z].height, g_sdl.texture_info[z].start);
		z++;
	}*/
	closedir(dir);
}