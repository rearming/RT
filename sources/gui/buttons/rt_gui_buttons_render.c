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

	text_surface = TTF_RenderText_Solid(g_gui.font, btn.text,
										get_color_from_hex(FONT_COL));
	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else if (btn.state == non_event)
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	else
		color = btn.color;
	render_border(&btn, BTN_BORDER, get_color_from_hex(GUI_BG));
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

void		render_button_without_border(t_transform btn)
{
	SDL_Surface *text_surface;
	SDL_Color	color;
	SDL_Rect 	label;

	text_surface = TTF_RenderText_Solid(g_gui.font, btn.text,
										get_color_from_hex(FONT_COL));
	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else if (btn.state == non_event)
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	else
		color = btn.color;
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

void		render_button_without_centered(t_transform btn)
{
	SDL_Surface *text_surface;
	SDL_Color	color;

	text_surface = TTF_RenderText_Solid(g_gui.font, btn.text,
										get_color_from_hex(FONT_COL));
	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else if (btn.state == non_event)
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	else
		color = btn.color;
	render_border(&btn, BTN_BORDER, get_color_from_hex(GUI_BG));
	SDL_FillRect(g_gui.surface,
				 &(btn.rect),
				 SDL_MapRGBA(
						 g_gui.surface->format,
						 color.r,
						 color.g,
						 color.b,
						 color.a));
	SDL_BlitSurface(text_surface, NULL, g_gui.surface, &(btn.rect));
	SDL_FreeSurface(text_surface);
}

void		render_button_without_anything(t_transform btn)
{
	SDL_Surface *text_surface;
	SDL_Color	color;

	text_surface = TTF_RenderText_Solid(g_gui.font, btn.text,
										get_color_from_hex(FONT_COL));
	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else if (btn.state == non_event)
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
	else
		color = btn.color;
	SDL_FillRect(g_gui.surface,
				 &(btn.rect),
				 SDL_MapRGBA(
						 g_gui.surface->format,
						 color.r,
						 color.g,
						 color.b,
						 color.a));
	SDL_BlitSurface(text_surface, NULL, g_gui.surface, &(btn.rect));
	SDL_FreeSurface(text_surface);
}

void		update_all_algo_buttons(void)
{
	int	j;

	j = 0;
	while (j < algo_btn_count)
	{
		if (g_gui.obj[j].action != g_gui.render_algo)
		{
			g_gui.obj[j].state = non_event;
			render_button(g_gui.obj[j]);
		}
		j++;
	}

}
