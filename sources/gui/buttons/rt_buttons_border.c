#include "rt.h"
#include "rt_gui.h"

void		 		cut_rect(SDL_Rect *rect, int px)
{
	rect->x += px;
	rect->y += px;
	rect->w -= 2 * px;
	rect->h -= 2 * px;
}

void				render_border(t_transform *btn, int px, SDL_Color color)
{
	SDL_Rect	button;

	button = btn->rect;
	cut_rect(&(btn->rect), px);
	SDL_FillRect(g_gui.surface,
				 &(button),
				 SDL_MapRGBA(
						 g_gui.surface->format,
						 color.r,
						 color.g,
						 color.b,
						 color.a));
}
