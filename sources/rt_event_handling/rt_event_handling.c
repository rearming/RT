#include "rt.h"
#include "rt_gui.h"
#include "rt_events.h"
#include "rt_opencl.h"

//# define WIN_RATIO ((float)WIN_WIDTH / WIN_HEIGHT)
//# define INVERSE_WIN_RATIO ((float)WIN_HEIGHT / WIN_WIDTH)
//# define D_E_KARMATSKIY (INVERSE_WIN_RATIO * INVERSE_WIN_RATIO)
//# define D_I_MAZOHIN (WIN_RATIO * WIN_RATIO)

float		d_i_mazokhin(int w, int h)
{
	const float win_ratio = (float)w / h;

	return (win_ratio * win_ratio);
}

float		d_e_karmatsky(int w, int h)
{
	const float win_ratio = (float)h / w;

	return (win_ratio * win_ratio);
}



bool		rt_handle_window_event(SDL_Event *event, t_rt *rt)
{
	int w;
	int h;
	int x;
	int y;

	SDL_GetWindowSize(g_sdl.win, &w, &h);

	if (event->window.event == SDL_WINDOWEVENT_MOVED){
		if (event->window.windowID == RT_WIN_ID)
		{

			SDL_SetWindowPosition(g_gui.win_tool, w + event->window.data1, event->window.data2);
		}
		else if (event->window.windowID == GUI_WIN_ID)
		{
			SDL_SetWindowPosition(g_sdl.win,  event->window.data1 - w, event->window.data2);
		}
	}
	else if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		SDL_GetWindowPosition(g_sdl.win, &x, &y);
		SDL_SetWindowPosition(g_gui.win_tool, x + w, y);
		rt->scene.camera.viewport_width = ((float)w / h) < 1 ? d_i_mazokhin(w, h) : 1;
		rt->scene.camera.viewport_height = ((float)w / h) > 1 ? d_e_karmatsky(w, h) : 1;
		return (true);
	}
	return (false);
}

void		handle_event(SDL_Event *event, t_rt *rt)
{
	const bool	key_event_handled = rt_handle_key_event(event, rt);
	const bool	mouse_event_handled = rt_handle_mouse_event(event, rt);
	const bool	tools_event_handled = rt_handle_event_gui(event, rt);
	const bool	window_event_handled = rt_handle_window_event(event, rt);

	if (key_event_handled || mouse_event_handled || tools_event_handled || window_event_handled)
	{
		rt_camera_move(&rt->scene.camera, &rt->events);
		rt_render(rt, &rt_opencl_render);
	}

}
