#include "rt.h"
#include "rt_gui.h"

void		rt_sdl_init(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		rt_raise_error(ERR_SDL_INIT);
	if (!(g_sdl.win = SDL_CreateWindow(WIN_TITLE,
			0, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		rt_raise_error(ERR_SDL_WIN);
#ifdef RT_GUI_H
	if (!(g_gui.win_tool = SDL_CreateWindow(RT_GUI_NAME,
			WIN_WIDTH, SDL_WINDOWPOS_CENTERED,
			WIN_GUI_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL)))
		rt_raise_error(ERR_SDL_WIN);
#endif
	if (!(g_sdl.rend = SDL_CreateRenderer(g_sdl.win, -1,
			SDL_RENDERER_ACCELERATED)))
		rt_raise_error(ERR_SDL_RENDER);
	if (!(g_sdl.texture = SDL_CreateTexture(g_sdl.rend,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		rt_raise_error(ERR_SDL_TEXTURE_CREATE);
}
