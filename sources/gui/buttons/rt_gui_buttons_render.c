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
	SDL_Surface *text_surface;
	SDL_Color	color;
	SDL_Rect 	label;

	text_surface = TTF_RenderText_Solid(g_gui.subtitle, btn.text,
										get_color_from_hex(FONT_COL));
	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else if (btn.state == non_event)
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	else
		color = btn.color;
	render_border(&btn, DEFAULT_BORDER, get_color_from_hex(GUI_BG));
	label = centered_label(btn.rect, text_surface);
	SDL_FillRect(g_gui.surface,
				 &(btn.rect),
				 SDL_MapRGBA(
						 g_gui.surface->format,
						 color.r,
						 color.g,
						 color.b,
						 color.a));
	SDL_BlitSurface(text_surface, NULL, g_gui.surface, &label);
	SDL_FreeSurface(text_surface);
}


void		render_button_with_params(t_transform btn, TTF_Font *font, int px)
{
	SDL_Surface *text_surface;
	SDL_Color	color;
	SDL_Rect 	label;

	text_surface = TTF_RenderText_Solid(font, btn.text,
										get_color_from_hex(FONT_COL));
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
	label = centered_label(btn.rect, text_surface);
	SDL_FillRect(g_gui.surface,
				 &(btn.rect),
				 SDL_MapRGBA(g_gui.surface->format,
						 color.r,
						 color.g,
						 color.b,
						 color.a));
	SDL_BlitSurface(text_surface, NULL, g_gui.surface, &label);
	SDL_FreeSurface(text_surface);
}

void		auto_render_button(int i)
{
	if  (g_gui.obj[i].type & PANEL)
		render_button_with_params(g_gui.obj[i], g_gui.body, 0);
	else
		render_button(g_gui.obj[i]);
}

void		render_all_buttons(void)
{
	int	i;

	i = 0;
	while (i < btn_count)
	{

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
		auto_render_button(i++);
	}
}
