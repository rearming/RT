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

void		create_screenshot(void)
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



void	create_screenshot_зтп(void)
{
	SDL_Surface *surface;
	char *file;

	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels, surface->pitch);
	file = name_generator();
	stbi_write_png(file, WIN_WIDTH, WIN_HEIGHT, 1, (Uint32 *)surface->pixels, WIN_WIDTH);
	ft_strdel(&file);
}