/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mouse_event_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"
#include "rt_window_params.h"

bool		rt_handle_mouse_event(SDL_Event *event, t_rt *rt)
{
	bool	event_handled;

	event_handled = false;
	if (event->type == SDL_MOUSEMOTION && SDL_GetRelativeMouseMode())
	{
		rt->scene.camera.rotation.x -=
				event->motion.yrel * ROTATION_SPEED * WIN_RATIO;
		rt->scene.camera.rotation.y += event->motion.xrel * ROTATION_SPEED;
		event_handled = true;
	}
	return (event_handled);
}
