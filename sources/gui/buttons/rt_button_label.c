#include "rt_gui.h"

SDL_Rect	centered_label( SDL_Rect button, SDL_Surface *sur)
{
	SDL_Rect centered;

	centered = (SDL_Rect){0, 0 , 0 ,0};
	if (sur)
	{
		centered.x = button.x + button.w / 2 - sur->w / 2;
		centered.y = button.y + button.h / 2 - sur->h / 2;
		centered.w = sur->w;
		centered.h = sur->h;
	}

	return (centered);
}