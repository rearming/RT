#include "rt.h"
#include "rt_gui.h"

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

void		init_other_buttons(void)
{
	SDL_Rect	rect;
	rect = (SDL_Rect){.x = 0, .y = WIN_HEIGHT - GUI_FOOTER,
			.h = 100, .w = WIN_GUI_WIDTH};
	g_gui.obj[scr_sbtn] = (t_transform){ .rect = rect,
			.state = non_event, .text = SCREENSHOT_LABEL, .action = scr_sbtn,
			.callback = button_callback, .type = SCREENSHOT,
			.color = get_color_from_hex(COL_GREEN)};
}
