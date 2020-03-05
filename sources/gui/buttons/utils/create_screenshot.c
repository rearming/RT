//#include <tclDecls.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "rt_gui.h"
#include "rt.h"
#include "time.h"


char*		get_time(void)
{
	char			*time_;
	const time_t	cur = time(NULL);

//	if (cur == ((time_t) - 1))
//		rt_raise_error(SMTH);
	time_ = ctime(&cur);
	return (time_);
}

char		*name_generator(void)
{
	char *filename;

	filename = ft_strjoin(ft_strjoin("Screenshot ", get_time()), ".png");
	return (filename);
}

void		create_screenshot_(void)
{
	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	SDL_Surface *surface;
	static int postfix;
	char *file;

	if (!postfix)
		postfix = 1;
	surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels, surface->pitch);
	file = ft_strjoin(ft_strjoin("Screenshot", ft_itoa(postfix)), ".bmp");
	postfix++;
	SDL_SaveBMP(surface, file);
	ft_strdel(&file);
	SDL_FreeSurface(surface);
}


//void	copy_color_map(uint32_t **map, SDL_Surface *sur)
//{
//	int i;
//
//	i = 0;
//	while (i < WIN_WIDTH < WIN_HEIGHT)
//	{
//		*map[i] = (uint32_t)sur->pixels[i];
//	}
//}


void	create_screenshot(void)
{
	SDL_Surface *surface;
	char *file;
	uint32_t *color_map;
	int i;
	int j;


	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels, surface->pitch);
	color_map = rt_safe_malloc(WIN_HEIGHT * WIN_WIDTH);
//	copy_color_map(&color_map, surface);
	file = name_generator();
	stbi_write_png(file, WIN_WIDTH, WIN_HEIGHT, 1, (uint32_t *)surface->pixels, WIN_WIDTH);
	ft_strdel(&file);
}