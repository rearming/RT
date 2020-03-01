#include "rt.h"
#include "rt_gui.h"

bool rt_handle_event_gui(SDL_Event *event, t_rt *rt)
{
	bool	event_handled;
	int 	i;
	t_btn	now;

	if (event->window.windowID != GUI_WIN_ID)
		return false;
	event_handled = false;
	i = 0;
	now = g_gui.render_algo;
	while (i < algo_btn_count)
	{
		if (g_gui.obj[i].callback(&g_gui.obj[i], event, rt))
		{
			render_button(g_gui.obj[i]);
			event_handled = true;
		}
		if (now != g_gui.render_algo)
		{
			update_all_algo_buttons();
		}
		i++;
	}
	i = 0;
	while (i < other_btn_count)
	{
		if (g_gui.obj[i + algo_btn_count].callback(&g_gui.obj[i + algo_btn_count], event, rt))
		{
			render_button(g_gui.obj[i + algo_btn_count]);
			event_handled = true;
		}
		i++;
	}
	SDL_UpdateWindowSurface(g_gui.win_tool);
	return (event_handled);
}