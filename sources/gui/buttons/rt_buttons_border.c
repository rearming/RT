#include "rt.h"
#include "rt_gui.h"

static void 		cut_rect(t_transform *btn, int px)
{
	btn->rect.x += px;
	btn->rect.y += px;
	btn->rect.w -= 2 * px;
	btn->rect.h -= 2 * px;
}

void				render_border(t_transform *btn, int px, SDL_Color color)
{
	SDL_Rect	button;

	button = btn->rect;
	cut_rect(btn, px);
	SDL_FillRect(g_gui.surface,
				 &(button),
				 SDL_MapRGBA(
						 g_gui.surface->format,
						 color.r,
						 color.g,
						 color.b,
						 color.a));
}
