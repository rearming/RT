#include "rt.h"
#include "stb_image.h"
# include <dirent.h>

void	rt_textures_init(void)
{
	t_texture_info		*texture_info = rt_safe_malloc(TEXTURE_NUM * sizeof(t_texture_info));
	int i;
	DIR *dir;
	struct dirent *entry;
	char *tmp;

	dir = opendir("textures/skysphere/");
	if (!dir)
		rt_raise_error(ERR_INVALID_TEXRTURE_DIR);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		if (!(tmp = ft_strjoin("textures/skysphere/", entry->d_name)))
			exit(-1);
		g_sdl.texture_list = stbi_load(tmp, &texture_info[0].width, &texture_info[0].height, &texture_info[0].bpp, 0);
		free(tmp);
		if (g_sdl.texture_list == NULL)
			return (rt_raise_error(ERR_SDL_TEXTURE_CREATE));
		printf("%i %s width = %i height = %i\n", i, entry->d_name, texture_info[0].width, texture_info[0].height);
		i++;
	}
	closedir(dir);
	for (int t = 0; t < TEXTURE_NUM; ++t)
	{

		stbi_uc *one_texture = stbi_load("texture.jpg", &texture_info[t].width, &texture_info[t].height, &texture_info[t].bpp, 0);


	}


}