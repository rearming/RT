#include "rt.h"
#include "rt_gui.h"

float		count_percent(char *text, char *field)
{
	const size_t joined_len = ft_strlen(text) + ft_strlen(field);
	const size_t text_len = ft_strlen(text);

	return ((float)text_len / (float)joined_len);
}

void		render_text_box(t_transform btn, t_scene scene)
{
	SDL_Rect	text;
	SDL_Rect	field;
	SDL_Color	color;

	if (btn.state == hidden)
		return ;
	if (btn.focus == true)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	render_rect(g_gui.surface, &(btn.rect), color);
	text = (SDL_Rect){.x = btn.rect.x, .y = btn.rect.y, .h = btn.rect.h};
	text.w = (int)((float)btn.rect.w * count_percent(btn.text, btn.field));
	field = (SDL_Rect){.x = btn.rect.x + text.w,
					.y = btn.rect.y, .h = btn.rect.h};
	field.w = btn.rect.w - text.w;
	render_text(g_gui.body, btn.text, text);
	render_text(g_gui.body, btn.field, field);
}
