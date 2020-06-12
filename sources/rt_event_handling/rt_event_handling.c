/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_event_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"
#include "rt_events.h"
#include "rt_opencl.h"
#include "rt_window_params.h"

bool		rt_handle_window_event(SDL_Event *event, t_rt *rt)
{
	SDL_Rect win;

	SDL_GetWindowSize(g_sdl.win, &win.w, &win.h);
	if (event->window.event == SDL_WINDOWEVENT_MOVED)
	{
		if (event->window.windowID == RT_WIN_ID)
			SDL_SetWindowPosition(g_gui.win_tool,
					win.w + event->window.data1, event->window.data2);
		else if (event->window.windowID == GUI_WIN_ID)
			SDL_SetWindowPosition(g_sdl.win, event->window.data1 - win.w,
					event->window.data2);
	}
	if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		SDL_GetWindowPosition(g_sdl.win, &win.x, &win.y);
		SDL_SetWindowPosition(g_gui.win_tool, win.x + win.w, win.y);
		rt->scene.camera.viewport_width = (float)win.w / (float)win.h;
		rt->scene.camera.viewport_height = 1;
		return (true);
	}
	return (false);
}

void		rt_check_render_state(
		uint32_t *render_action,
		uint32_t *render_options,
		uint32_t render_state)
{
	(void)render_action;
	if (render_state & STATE_NO_MESH)
		rt_unset_bit(render_options, RENDER_MESH | RENDER_MESH_VTEXTURES
		| RENDER_BACKFACE_CULLING);
	if (render_state & STATE_NO_TEXTURES)
		rt_unset_bit(render_options, RENDER_TEXTURES);
	if (render_state & STATE_NO_SKYBOX)
		rt_unset_bit(render_options, RENDER_SKYBOX);
}

static bool	handle_all_events(t_rt *rt, SDL_Event *events, int events_num)
{
	bool	key_event_handled;
	bool	mouse_event_handled;
	bool	gui_event_handled;
	bool	window_event_handled;
	int		i;

	key_event_handled = false;
	mouse_event_handled = false;
	gui_event_handled = false;
	window_event_handled = false;
	i = 0;
	while (i < events_num)
	{
		key_event_handled = rt_handle_key_event(&events[i], rt);
		mouse_event_handled = rt_handle_mouse_event(&events[i], rt);
		gui_event_handled = rt_handle_event_gui(&events[i], rt);
		window_event_handled = rt_handle_window_event(&events[i], rt);
		i++;
	}
	return (key_event_handled | mouse_event_handled
	| gui_event_handled | window_event_handled);
}

void		handle_event(t_rt *rt, SDL_Event *events, int events_num)
{
	if (handle_all_events(rt, events, events_num) || rt->events)
	{
		rt_camera_move(&rt->scene.camera, rt->events);
		if (rt_camera_changed(&rt->scene.camera))
			rt->render_actions |= ACTION_CAMERA_CHANGED;
		rt_check_render_state(&rt->render_actions,
				&rt->render_options, rt->render_state);
		rt_render(rt, &rt_opencl_render);
	}
}
