#include "rt.h"
#include "rt_gui.h"

void		render_text_box_(t_transform btn)//todo test this shit
{
	t_transform label;
	t_transform text;

	label.rect = btn.rect;
	label.rect.w /= 2;
	text.rect = label.rect;
	text.rect.y += text.rect.w;

	label = (t_transform){.state = non_event, .action = btn.action,
			.callback = button_callback, .color = get_color_from_hex(COL_RED)};
	ft_strcpy(text.text, btn.field);
	text = (t_transform){.state = non_event, .action = btn.action,
			.callback = button_callback, .color = get_color_from_hex(COL_DARK_PURPLE)};
	render_button_with_params(label, g_gui.body, 0);
	render_button_with_params(text, g_gui.body, 0);
}

float		count_percent(char *text, char *field)
{
	const size_t joined_len = ft_strlen(text) + ft_strlen(field);
	const size_t text_len = ft_strlen(text);
	return ((float)text_len / (float)joined_len);
}

void		render_text_box(t_transform btn)
{
	SDL_Rect	text;
	SDL_Rect	field;
	SDL_Color	color;

	if (btn.state == hidden)
		return ;
	render_rect(g_gui.surface, &(btn.rect), btn.color);

	text = (SDL_Rect){.x = btn.rect.x, .y = btn.rect.y, .h = btn.rect.h};
	text.w = (int)((float)btn.rect.w * count_percent(btn.text, btn.field));
	field = (SDL_Rect){.x = btn.rect.x + text.w, .y = btn.rect.y, .h = btn.rect.h};
	field.w = btn.rect.w - text.w;
	render_text(g_gui.body, btn.text, text);
	render_text(g_gui.body, btn.field, field);


}
