/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:41 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/20 15:55:31 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"
#include "rt.h"

void		render_button(t_transform btn)
{
	SDL_Color	color;
	t_ttf		label;

	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else if (btn.state == non_event)
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	else
		color = btn.color;
	render_border(&btn, DEFAULT_BORDER, get_color_from_hex(GUI_BG));
	label = get_centered_label(g_gui.subtitle, btn.text, btn.rect);
	render_rect(g_gui.surface, &(btn.rect), color);
	SDL_BlitSurface(label.sur, NULL, g_gui.surface, &(label.rect));
	SDL_FreeSurface(label.sur);
}

void		render_button_with_params(t_transform btn, TTF_Font *font, int px)
{
	SDL_Color	color;

	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else if (btn.state == non_event)
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	else
		color = btn.color;
	if (!px)
		render_border(&btn, px, get_color_from_hex(GUI_BG));
	render_rect(g_gui.surface, &(btn.rect), color);
	render_text(font, btn.text, btn.rect);
}

void		auto_render_button(int i)
{
	if  (g_gui.obj[i].type & PANEL)
		render_button_with_params(g_gui.obj[i], g_gui.body, 0);
	else if ((g_gui.obj[i].type & TEXT_BOX)
	&& g_gui.obj[i].state != hidden)
		render_text_box(g_gui.obj[i]);
	else if (g_gui.obj[i].state != hidden)
		render_button(g_gui.obj[i]);
}

void		render_all_buttons(void)
{
	int	i;
	SDL_Color bg;
	SDL_Rect *rect;

	i = 0;
	bg = get_color_from_hex(PANEL_BG);
	rect = &(SDL_Rect){ .x = 0, .y = PANEL_Y, .h = PANEL_HEIGHT, .w = PANEL_WIDTH};
	cut_rect(rect, PANEL_BORDER);
	render_rect(g_gui.surface, rect, bg);
	while (i < btn_count)
	{
		if (g_gui.obj[i].callback == NULL)
			rt_raise_error(BTN_TROUBLE);
		if (g_gui.obj[i].type == RENDER_BTN)
		{
			if (g_gui.obj[i].action != g_gui.render_algo)
				g_gui.obj[i].state = non_event;
			else
				g_gui.obj[i].state = click;
		}
		if (g_gui.obj[i].type == PANEL)
		{
			if (g_gui.obj[i].action != g_gui.panel)
				g_gui.obj[i].state = non_event;
			else
				g_gui.obj[i].state = click;
		}
		if (g_gui.obj[i].type & TEXT_BOX)
		{
			if (g_gui.obj[i].type & (1 << (g_gui.panel)))
				g_gui.obj[i].state = label;
			else
				g_gui.obj[i].state = hidden;
		}
		auto_render_button(i++);
	}
	SDL_UpdateWindowSurface(g_gui.win_tool);
}
