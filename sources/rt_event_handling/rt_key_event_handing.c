/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_event_handing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_events.h"
#include "rt_gui.h"

static inline void		rt_add_key_event(
		uint32_t *events,
		SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		rt_set_bit(events, EVENT_W);
	if (scancode == SDL_SCANCODE_S)
		rt_set_bit(events, EVENT_S);
	if (scancode == SDL_SCANCODE_A)
		rt_set_bit(events, EVENT_A);
	if (scancode == SDL_SCANCODE_D)
		rt_set_bit(events, EVENT_D);
	if (scancode == SDL_SCANCODE_SPACE)
		rt_set_bit(events, EVENT_SPACE);
	if (scancode == SDL_SCANCODE_X)
		rt_set_bit(events, EVENT_LSHIFT);
}

static inline void		remove_key_event(
		uint32_t *events,
		SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		rt_unset_bit(events, EVENT_W);
	if (scancode == SDL_SCANCODE_S)
		rt_unset_bit(events, EVENT_S);
	if (scancode == SDL_SCANCODE_A)
		rt_unset_bit(events, EVENT_A);
	if (scancode == SDL_SCANCODE_D)
		rt_unset_bit(events, EVENT_D);
	if (scancode == SDL_SCANCODE_SPACE)
		rt_unset_bit(events, EVENT_SPACE);
	if (scancode == SDL_SCANCODE_X)
		rt_unset_bit(events, EVENT_LSHIFT);
}

void sync_options_buttons(uint64_t options, u_int64_t states)
{
	int i;

	i = msh_btn;
	while (i <= sb_btn)
	{
		g_gui.obj[i].state = (options & g_gui.obj[i].bit) ?
				(click) : (non_event);
		i++;
	}
	while (i <= tunes_btn)
	{
		g_gui.obj[i].state = (states & g_gui.obj[i].bit) ?
				(click) : (non_event);
		i++;
	}
}

void sync_rt_and_gui(t_scene scene, uint64_t options, uint64_t states)
{
	const uint64_t	render_num = (options & (0b111)) - 1;

	g_gui.render_algo = render_num;
	g_gui.obj[render_num].state = click;
	render_button(g_gui.obj[render_num]);
//	sync_options_buttons(options, states);
	render_all_buttons(scene);
	SDL_UpdateWindowSurface(g_gui.win_tool);
}

static inline void		rt_handle_keypress(SDL_Event *event, t_rt *rt)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(rt_exit_clean());
	if (event->key.keysym.scancode == SDL_SCANCODE_I)
		rt_switch_bit(&rt->events, EVENT_INFO);
	if (event->key.keysym.scancode == SDL_SCANCODE_L)
		SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
	if (event->key.keysym.scancode == SDL_SCANCODE_R)
	{
		rt_set_render_algo(&rt->render_options, RENDER_RAYTRACE);
		sync_rt_and_gui(rt->scene, rt->render_options, 0);
	}
	if (event->key.keysym.scancode == SDL_SCANCODE_P)
	{
		rt_set_render_algo(&rt->render_options, RENDER_PATHTRACE);
		rt_set_bit(&rt->render_actions, ACTION_PATHTRACE);
		sync_rt_and_gui(rt->scene, rt->render_options, 0);
	}
	rt_handle_keypress2(event, rt);
}

bool					rt_handle_key_event(SDL_Event *event, t_rt *rt)
{
	bool	event_handled;

	event_handled = false;
	if (event->type == SDL_KEYUP)
	{
		remove_key_event(&rt->events, event->key.keysym.scancode);
		event_handled = true;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		rt_handle_keypress(event, rt);
		rt_add_key_event(&rt->events, event->key.keysym.scancode);
		event_handled = true;
	}
	return (event_handled);
}
