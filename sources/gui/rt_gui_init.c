/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:51 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/20 15:55:11 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"


void		change_render_algo(short algo, t_rt *rt)
{
	rt_set_render_algo(&rt->renderer_flags, 1 << (algo));
}

void		init_algo_buttons(void)
{
	SDL_Rect	rect;
	short		algo;

	algo = g_gui.render_algo;
	rect = (SDL_Rect){.x = 0, .y = GUI_TITLE, .h = 100, .w = WIN_GUI_WIDTH / 2};
	g_gui.obj[pt_btn] = (t_transform){ .rect = rect, .state = non_event,
			.text = PATH_TRACE_LABEL, .callback = button_callback, .action = pt_btn,
			.type = RENDER_BTN, .color = get_color_from_hex(COL_RED)};
	rect.x += WIN_GUI_WIDTH / 2;
	g_gui.obj[rt_btn] = (t_transform){ .rect = rect, .state = non_event,
			.text = RAY_TRACE_LABEL, .callback = button_callback, .action = rt_btn,
			.type = RENDER_BTN, .color = get_color_from_hex(COL_BLUE)};
	if (algo == pt_btn)
		g_gui.obj[pt_btn].state = click;
	else if (algo == rt_btn)
		g_gui.obj[rt_btn].state = click;
}

void		create_title(void)
{
	SDL_Rect	rect;
	t_transform	title;

	rect = (SDL_Rect){.x = 0, .y = 0, .h = 100, .w = WIN_GUI_WIDTH};
	title = (t_transform){ .rect = rect,
			.state = label, .text = RT_GUI_TITLE,
			.color = get_color_from_hex(0xFFFFFF)};
	render_button_without_border(title);
}

void		init_other_buttons(void)
{
	SDL_Rect	rect;
	rect = (SDL_Rect){.x = 0, .y = WIN_HEIGHT - GUI_FOOTER,
				   .h = 100, .w = WIN_GUI_WIDTH};
	g_gui.obj[algo_btn_count + scr_sbtn] = (t_transform){ .rect = rect,
			.state = non_event, .text = SCREENSHOT_LABEL, .action = scr_sbtn,
			.callback = button_callback, .type = SCREENSHOT,
			.color = get_color_from_hex(COL_GREEN)};
}

void		init_gui(uint64_t algo)
{
	int			i;
	SDL_Color	bg;

	TTF_Init();
	bg = get_color_from_hex(GUI_BG);
	g_gui.obj = rt_safe_malloc(sizeof(t_transform) * btn_count);
	g_gui.surface = SDL_GetWindowSurface(g_gui.win_tool);


	SDL_FillRect(g_gui.surface, NULL,
			SDL_MapRGB(g_gui.surface->format, bg.r, bg.g, bg.b));
	g_gui.font = TTF_OpenFont(FONT_PATH, FONT_SIZE + 10);
	create_title();
	TTF_CloseFont(g_gui.font);
	g_gui.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	g_gui.render_algo = ((algo & 0b111) - 1);
	init_algo_buttons();
	init_other_buttons();
	i = 0;
	while (i < btn_count)
		render_button(g_gui.obj[i++]);
	SDL_UpdateWindowSurface(g_gui.win_tool);
}
