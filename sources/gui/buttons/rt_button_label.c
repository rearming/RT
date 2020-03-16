#include "rt.h"
#include "rt_gui.h"

t_ttf	get_centered_label(TTF_Font *font, char *text, SDL_Rect rect)
{
	t_ttf		label;
	SDL_Rect	centered;

	label.sur = TTF_RenderText_Solid(font,
			text, get_color_from_hex(FONT_COL));
	centered = (SDL_Rect){0, 0 , 0 ,0};
	if (label.sur)
	{
		centered.x = rect.x + rect.w / 2 - label.sur->w / 2;
		centered.y = rect.y + rect.h / 2 - label.sur->h / 2;
		centered.w = label.sur->w;
		centered.h = label.sur->h;
	}
	label.rect = centered;
	return (label);
}


void	render_text(TTF_Font *font, char *text, SDL_Rect rect)
{
	const t_ttf	label = get_centered_label(font, text, rect);

	if (label.sur->h < rect.h && label.sur->w < rect.w)
		SDL_BlitSurface(label.sur, NULL, g_gui.surface, &(label.rect));
	SDL_FreeSurface(label.sur);
}

void	render_rect(SDL_Surface *sur, SDL_Rect *rect, SDL_Color col)
{
	SDL_FillRect(sur, rect, SDL_MapRGBA(sur->format,
			col.r, col.g, col.b, col.a));
}