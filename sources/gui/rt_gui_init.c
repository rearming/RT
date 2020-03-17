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
	g_gui.obj[obj_pos] = (t_transform){ .rect = rect,
			.state = non_event, .text = POSITION_LABEL, .action = obj_pos,
			.callback = button_callback, .type = PANEL,
			.color = get_color_from_hex(NONE)};
	rect.x += rect.w;
	g_gui.obj[obj_param] = (t_transform){ .rect = rect,
			.state = non_event, .text = PARAMETERS_LABEL, .action = obj_param,
			.callback = button_callback, .type = PANEL,
			.color = get_color_from_hex(NONE)};

}

void		init_font()
{
	TTF_Init();
	if ((g_gui.title = TTF_OpenFont(FONT_PATH, TITLE_FONT_SIZE)) == NULL)
		rt_raise_error(FONT_ERROR);
	if ((g_gui.subtitle = TTF_OpenFont(FONT_PATH, SUBTITLE_FONT_SIZE)) == NULL)
		rt_raise_error(FONT_ERROR);
	if ((g_gui.body = TTF_OpenFont(MAGMAWAVE_CAPS_FONT, BODY_FONT_SIZE)) == NULL)
		rt_raise_error(FONT_ERROR);
}

void		fill_surfaces()
{
	SDL_Color	bg;
	SDL_Rect	*rect;

	bg = get_color_from_hex(GUI_BG);
	render_rect(g_gui.surface, NULL, bg);
	bg = get_color_from_hex(PANEL_BG);
	rect = &(SDL_Rect){ .x = 0, .y = PANEL_Y, .h = PANEL_HEIGHT, .w = PANEL_WIDTH};
	cut_rect(rect, PANEL_BORDER);
	render_rect(g_gui.surface, rect, bg);
}

void		init_cam_text_box(SDL_Rect rect)
{
	const SDL_Color color = get_color_from_hex(BTN_COLOR_CLICK);
//	const SDL_Color color = get_color_from_hex(COL_RED);
//
//	render_text(g_gui.body, "Position", rect);
//	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[c_pos_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Pos X", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[c_pos_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Pos Y", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[c_pos_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Pos Z", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[c_angle_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Angle X", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[c_angle_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Angle Y", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[c_angle_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Angle Z", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
}

void		init_pos_text_box(SDL_Rect rect)
{
	const SDL_Color color = get_color_from_hex(BTN_COLOR_CLICK);

	g_gui.obj[obj_pos_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Pos X", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[obj_pos_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Pos Y", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[obj_pos_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Pos Z", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[obj_angle_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Angle X", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[obj_angle_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Angle Y", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[obj_angle_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Angle Z", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
}

void		init_params_text_box(SDL_Rect rect)
{
	const SDL_Color color = get_color_from_hex(BTN_COLOR_CLICK);

	g_gui.obj[param_pos_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Pos X", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[param_pos_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Pos Y", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[param_pos_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Pos Z", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[param_angle_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Angle X", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[param_angle_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Angle Y", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE * 2;
	g_gui.obj[param_angle_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Angle Z", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
}



void		init_text_box()
{
	SDL_Rect rect;

	rect = (SDL_Rect){.x = (WIN_GUI_WIDTH - PANEL_BUTTON_WIDTH * 2) / 2,
				   .y = 300,
				   .w = PANEL_BUTTON_WIDTH * 2,
				   .h = BTN_DEFAULT_SIZE};
	init_cam_text_box(rect);
	init_params_text_box(rect);
	init_pos_text_box(rect);

}

void		init_gui(uint64_t algo)
{
	g_gui.render_algo = ((algo & 0b111) - 1);
	g_gui.panel = camera_l;
	g_gui.obj = rt_safe_malloc(sizeof(t_transform) * (btn_count));
	init_font();
	if ((g_gui.surface = SDL_GetWindowSurface(g_gui.win_tool)) == NULL)
		rt_raise_error(GET_SURFACE_TROUBLE);
	fill_surfaces();
	create_title();
	init_algo_buttons();
	init_object_panel();
	init_other_buttons();
	init_text_box();
	render_all_buttons();
	SDL_UpdateWindowSurface(g_gui.win_tool);
}
