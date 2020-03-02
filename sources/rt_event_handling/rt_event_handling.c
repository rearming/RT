#include "rt.h"
#include "rt_gui.h"
#include "rt_events.h"
#include "rt_opencl.h"

void		resize_gui(int height)//TODO NEED DEBUG THIS FUNCTION
{
	int			i;
	float	k = height/(float)WIN_HEIGHT;
	SDL_Color	bg;
	bg = get_color_from_hex(arc4random());

	i = 0;
	printf("resize_gui launched\n");
	TTF_CloseFont(g_gui.font);
	g_gui.font = TTF_OpenFont(FONT_PATH, (int)(FONT_SIZE * k));
	SDL_FillRect(g_gui.surface, NULL,
				 SDL_MapRGB(g_gui.surface->format, bg.r, bg.g, bg.b));
	while (i < btn_count)
	{
		g_gui.obj[i].color = get_color_from_hex(arc4random());
		g_gui.obj[i].rect.h = (int)((float)g_gui.obj[i].rect.h * k);
		render_button(g_gui.obj[i]);
		printf("button [%i] rendered\n", i);
		i++;
	}

	SDL_UpdateWindowSurface(g_gui.win_tool);
	printf("func end\n");
}

bool		rt_handle_window_event(SDL_Event *event, t_rt *rt)
{
	SDL_Rect win;

	SDL_GetWindowSize(g_sdl.win, &win.w, &win.h);
 	if (event->window.event == SDL_WINDOWEVENT_MOVED)
 	{
		if (event->window.windowID == RT_WIN_ID)
			SDL_SetWindowPosition(g_gui.win_tool, win.w + event->window.data1, event->window.data2);
		else if (event->window.windowID == GUI_WIN_ID)
			SDL_SetWindowPosition(g_sdl.win, event->window.data1 - win.w, event->window.data2);
	}
	if  (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		SDL_GetWindowPosition(g_sdl.win, &win.x, &win.y);
		SDL_SetWindowPosition(g_gui.win_tool, win.x + win.w, win.y);
//		resize_gui(win.h);//TODO NEED DEBUG THIS FUNCTION
//			SDL_SetWindowSize(g_gui.win_tool, WIN_GUI_WIDTH, win.h);

		rt->scene.camera.viewport_width = (float)win.w / (float)win.h;
		rt->scene.camera.viewport_height = 1;
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
