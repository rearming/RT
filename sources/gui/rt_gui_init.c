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


void		create_title(void)
{
	SDL_Rect	rect;
	t_transform	title;

	rect = (SDL_Rect){.x = 0, .y = 0, .h = GUI_TITLE, .w = WIN_GUI_WIDTH};
	title = (t_transform){ .rect = rect,
			.state = label, .text = RT_GUI_TITLE,
			.color = get_color_from_hex(WHITE)};
	render_button_with_params(title, g_gui.title, 0);
}

//void		render_text_box(t_transform tb)
//{
//	SDL_Surface *text_surface;
//
//
//	text_surface = TTF_RenderText_Solid(g_gui.font, tb.text,
//										get_color_from_hex(FONT_COL));
//
//	SDL_FillRect(g_gui.surface,
//				 &(btn.rect),
//				 SDL_MapRGBA(
//						 g_gui.surface->format,
//						 color.r,
//						 color.g,
//						 color.b,
//						 color.a));
//	SDL_BlitSurface(text_surface, NULL, g_gui.surface, &(btn.rect));
//	SDL_FreeSurface(text_surface);
//}
////
//void		textbox_init()
//{
//	SDL_Rect	rect;
//
//	rect = (SDL_Rect){.x = 300, .y = 300,
//			.h = 100, .w = 100};
//	g_gui.obj[a_btn + o_btn + test_text_box] = 	(t_transform){ .rect = rect,
//			.state = non_event, .text = SCREENSHOT_LABEL, .action = scr_sbtn,
//			.callback = button_callback, .type = SCREENSHOT,
//			.color = get_color_from_hex(COL_GREEN)};
//}

void		init_object_panel()
{
	SDL_Rect rect;

	rect = (SDL_Rect){.x = PANEL_BORDER, .y = PANEL_Y,
				.h = BTN_DEFAULT_SIZE, .w = PANEL_BUTTON_WIDTH};
	g_gui.obj[camera_l] = (t_transform){ .rect = rect,
			.state = click, .text = CAMERA_LABEL, .action = camera_l,
			.callback = button_callback, .type = PANEL,
			.color = get_color_from_hex(NONE)};
	rect.x += rect.w;
	g_gui.obj[obj_l] = (t_transform){ .rect = rect,
			.state = non_event, .text = POSITION_LABEL, .action = obj_l,
			.callback = button_callback, .type = PANEL,
			.color = get_color_from_hex(NONE)};
	rect.x += rect.w;
	g_gui.obj[obj_pos] = (t_transform){ .rect = rect,
			.state = non_event, .text = PARAMETERS_LABEL, .action = obj_pos,
			.callback = button_callback, .type = PANEL,
			.color = get_color_from_hex(NONE)};

}

void		init_font()
{
	TTF_Init();
	g_gui.title = TTF_OpenFont(FONT_PATH, TITLE_FONT_SIZE);
	g_gui.subtitle = TTF_OpenFont(FONT_PATH, SUBTITLE_FONT_SIZE);
	g_gui.body = TTF_OpenFont(FONT_PATH, BODY_FONT_SIZE);
}

void		fill_surfaces()
{
	SDL_Color	bg;
	SDL_Rect	*rect;

	bg = get_color_from_hex(GUI_BG);
	SDL_FillRect(g_gui.surface, NULL,
				 SDL_MapRGB(g_gui.surface->format, bg.r, bg.g, bg.b));
	bg = get_color_from_hex(BTN_COLOR_CLICK);
	rect = &(SDL_Rect){ .x = 0, .y = PANEL_Y, .h = PANEL_HEIGHT, .w = PANEL_WIDTH};
	cut_rect(rect, PANEL_BORDER);
	SDL_FillRect(g_gui.surface, rect,
				 SDL_MapRGB(g_gui.surface->format, bg.r, bg.g, bg.b));
}

//void		render_text_box(t_transform btn)
//{
//	render_button()
//
//}

void		init_gui(uint64_t algo)
{

	g_gui.render_algo = ((algo & 0b111) - 1);
	g_gui.panel = camera_l;
	g_gui.obj = rt_safe_malloc(sizeof(t_transform) * (btn_count));
	init_font();
	g_gui.surface = SDL_GetWindowSurface(g_gui.win_tool);
	fill_surfaces();
	create_title();
	init_algo_buttons();
	init_object_panel();
	init_other_buttons();
	render_all_buttons();
//	init_text_box();
	SDL_UpdateWindowSurface(g_gui.win_tool);
}
