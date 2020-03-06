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


//SDL_Color**	copy_color_map(SDL_Color *map)
//{
//	SDL_Color costyl[WIN_HEIGHT][WIN_WIDTH];
//	int i, j;
//
//	i = 0;
//	while (i < WIN_HEIGHT)
//	{
//		j = 0;
//		while (j < WIN_WIDTH)
//		{
//			costyl[i][j] = map[i * WIN_WIDTH + j];
//			j++;
//		}
//		i++;
//	}
//	return costyl;
//}


SDL_Color *get_pixels_from_surface()
{
	SDL_Surface *surface;
	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	SDL_Color *color_map;


	color_map = rt_safe_malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(SDL_Color));
	surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels, surface->pitch);
	color_map = (SDL_Color *)surface->pixels;
	return (color_map);
}

void	create_screenshot_png(void)
{
	char *file;
	const Uint32 format= SDL_PIXELFORMAT_ARGB8888;
	SDL_Color *color_map;
	int i, j;
	SDL_Color **costyl;
	SDL_Surface *surface;
//	SDL_Color *color_map;

//	format = SDL_PIXELFORMAT_ARGB8888;



	costyl = rt_safe_malloc((WIN_HEIGHT ) * sizeof(SDL_Color *));
	i = -1;
	while (++i < WIN_HEIGHT + 1)
	{
		costyl[i] = rt_safe_malloc((WIN_WIDTH ) * sizeof(SDL_Color));
	}

	surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels, surface->pitch);
//	color_map = (SDL_Color *)rt_safe_malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(SDL_Color));
//	color_map = (SDL_Color *)surface->pixels;
	color_map = get_pixels_from_surface();
	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			costyl[i][j] = color_map[i * WIN_WIDTH + j];
			j++;
		}
		i++;
	}


	file = name_generator();
	stbi_write_png(file, WIN_WIDTH, WIN_HEIGHT, 1, color_map, WIN_WIDTH);
	ft_strdel(&file);
}

//void	create_fucking_