#include "rt.h"
#include "rt_gui.h"

t_ttf	get_centered_label(TTF_Font *font, char *text, SDL_Rect rect)
{
	t_ttf		label;
	SDL_Rect	centered;

	label.surface = TTF_RenderText_Solid(font,
			text, get_color_from_hex(FONT_COL));
	centered = (SDL_Rect){0, 0, 0, 0};
	if (label.surface)
	{
		centered.x = rect.x + rect.w / 2 - label.surface->w / 2;
		centered.y = rect.y + rect.h / 2 - label.surface->h / 2;
		centered.w = label.surface->w;
		centered.h = label.surface->h;
	}
	label.rect = centered;
	return (label);
}

void	render_text(TTF_Font *font, char *text, SDL_Rect rect)
{
	t_ttf	label;

	label = get_centered_label(font, text, rect);
	if (label.surface->h < rect.h && label.surface->w < rect.w)
		SDL_BlitSurface(label.surface, NULL, g_gui.surface, &(label.rect));
	SDL_FreeSurface(label.surface);
}

void	render_rect(SDL_Surface *sur, SDL_Rect *rect, SDL_Color col)
{
	SDL_FillRect(sur, rect, SDL_MapRGBA(sur->format,
			col.r, col.g, col.b, col.a));
}
