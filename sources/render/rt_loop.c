/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_opencl.h"
#include "rt_events.h"

void		rt_loop(t_rt *rt)
{
	SDL_Event		event;
	SDL_Event		events[MAX_EVENT_IN_LIST];
	int				event_num;

	event_num = 0;
	while (21)
	{
		while (SDL_PollEvent(&event) && event_num < MAX_EVENT_IN_LIST)
		{
			events[event_num] = event;
			event_num++;
		}
		if (event_num > 0)
		{
			handle_event(rt, events, event_num);
			event_num = 0;
		}
		if (rt_bit_isset(rt->render_options, RENDER_PATHTRACE))
			rt_render(rt, rt_opencl_render);
		if (event.type == SDL_QUIT
		|| event.window.event == SDL_WINDOWEVENT_CLOSE)
			break ;
	}
}
