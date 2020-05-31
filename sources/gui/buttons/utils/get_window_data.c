#include "rt.h"

SDL_Rect	get_window_data(void)
{
	SDL_Rect window;

	SDL_GetWindowSize(g_sdl.win, &(window.w), &(window.h));
	SDL_GetWindowPosition(g_sdl.win, &(window.x), &(window.y));
	return (window);
}
