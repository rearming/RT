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

t_transform	create_gui_obj(
		SDL_Rect		button,
		unsigned int	color,
		char			*text,
		void			*callback)
{
	t_transform		gui_obj;

	gui_obj.rect = button;
	gui_obj.color = get_color_from_hex(color);
	if (text != NULL)
		gui_obj.text = ft_strdup(text);
	else
		gui_obj.text = NULL;
	gui_obj.callback = callback;
	return (gui_obj);
}



void		change_render_algo(short algo, t_rt *rt)
{
	rt_set_render_algo(&rt->renderer_flags, 1 << (algo));
}

void		init_algo_buttons(void)
{
	SDL_Rect	rect;
	short		algo;

	algo = g_gui.render_algo;
	rect = (SDL_Rect){.x = 0, .y = 30, .h = 100, .w = WIN_GUI_WIDTH / 2};
	g_gui.obj[pt_btn] = (t_transform){ .rect = rect, .state = non_event,
			.text = PATH_TRACE_LABEL, .callback = button_callback, .action = pt_btn,
			.type = RENDER_BTN, .color = get_color_from_hex(COL_RED)};
	rect.x += WIN_GUI_WIDTH / 2;
	g_gui.obj[rt_btn] = (t_transform){ .rect = rect,
			.text = RAY_TRACE_LABEL, .callback = button_callback, .action = rt_btn,
			.type = RENDER_BTN, .color = get_color_from_hex(COL_BLUE)};
	if (algo == pt_btn)
	{
		g_gui.obj[pt_btn].state = click;
		g_gui.obj[rt_btn].state = non_event;
	}
	else if (algo == rt_btn)
	{
		g_gui.obj[rt_btn].state = click;
		g_gui.obj[pt_btn].state = non_event;
	}
}

void		init_other_buttons(void)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){.x = 0, .y = WIN_HEIGHT - 150,
				   .h = 100, .w = WIN_GUI_WIDTH};
	g_gui.obj[algo_btn_count + scr_sbtn] = (t_transform){ .rect = rect,
			.state = non_event, .text = SCREENSHOT_LABEL, .action = scr_sbtn,
			.callback = button_callback, .type = SCREENSHOT,
			.color = get_color_from_hex(COL_GREEN)};
//	rect = (SDL_Rect){.x = 320, .y = 450,
//			.h = 100, .w = 100};
//	g_gui.obj[algo_btn_count + test_btn] = (t_transform){ .rect = rect,
//			.state = non_event, .text = "test", .action = test_btn,
//			.callback = button_callback, .type = NONE,
//			.color = get_color_from_hex(COL_GREEN)};
}

void		init_gui(uint64_t algo)
{
	int			i;
	SDL_Color	bg;

	TTF_Init();
	bg = get_color_from_hex(GUI_BG);
	g_gui.obj = rt_safe_malloc(sizeof(t_transform) * btn_count);
	g_gui.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	g_gui.surface = SDL_GetWindowSurface(g_gui.win_tool);
	SDL_FillRect(g_gui.surface, NULL,
			SDL_MapRGB(g_gui.surface->format, bg.r, bg.g, bg.b));
	g_gui.render_algo = ((algo & 0b111) - 1);
	init_algo_buttons();
	init_other_buttons();
	i = 0;
	while (i < btn_count)
		render_button(g_gui.obj[i++]);
	SDL_UpdateWindowSurface(g_gui.win_tool);
}
