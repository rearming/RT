//
// Created by Dyan Great on 17/03/2020.
//

#include "rt.h"
#include "rt_gui.h"

void		init_cam_text_box(SDL_Rect rect)
{
	const SDL_Color color = get_color_from_hex(BTN_COLOR_CLICK);

	g_gui.obj[c_pos_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Pos X", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_pos_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Pos Y", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_pos_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Pos Z", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_angle_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Angle X", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[c_angle_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Angle Y", .field = "cam",
			.state = label, .type = CAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
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
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[obj_pos_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Pos Y", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[obj_pos_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Pos Z", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[obj_angle_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Angle X", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[obj_angle_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Angle Y", .field = "pos",
			.state = hidden, .type = POS_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
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
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[param_pos_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Pos Y", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[param_pos_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Pos Z", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[param_angle_x] = (t_transform){.rect = rect, .action = c_pos_x,
			.callback = button_callback, .text = "Angle X", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[param_angle_y] = (t_transform){.rect = rect, .action = c_pos_y,
			.callback = button_callback, .text = "Angle Y", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
	rect.y += BTN_DEFAULT_SIZE;
	g_gui.obj[param_angle_z] = (t_transform){.rect = rect, .action = c_pos_z,
			.callback = button_callback, .text = "Angle Z", .field = "params",
			.state = hidden, .type = PARAM_TEXT_BOX, .color = color};
}

void		init_text_box()
{
	SDL_Rect rect;

	rect = (SDL_Rect){
			.x = (WIN_GUI_WIDTH - PANEL_BUTTON_WIDTH) / 2,
			.y = 300,
			.w = PANEL_BUTTON_WIDTH,
			.h = BTN_DEFAULT_SIZE};
	init_cam_text_box(rect);
	init_params_text_box(rect);
	init_pos_text_box(rect);
}
