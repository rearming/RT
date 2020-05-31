#include "rt.h"
#include "rt_gui.h"

bool	rt_handle_event_gui(SDL_Event *event, t_rt *rt)
{
	bool	event_handled;
	int		i;
	t_btn	now;
	t_btn	panel;

	if (event->window.windowID != GUI_WIN_ID)
		return (false);
	event_handled = false;
	i = 0;
	now = g_gui.render_algo;
	panel = g_gui.panel;
	while (i < btn_count)
	{
		if (g_gui.obj[i].callback(&g_gui.obj[i], event, rt))
		{
			auto_render_button(i, rt->scene);
			event_handled = true;
		}
		if (now != g_gui.render_algo || panel != g_gui.panel)
			render_all_buttons(rt->scene);
		i++;
	}
	SDL_UpdateWindowSurface(g_gui.win_tool);
	return (event_handled);
}
