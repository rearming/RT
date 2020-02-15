/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_render_callback.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 18:52:27 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/15 19:04:20 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

void		switch_render_algo(short algo, int btn, t_rt *rt, t_gui *gui)
{
	rt->opencl_params.render_algo = algo;

	disable_button(gui, gui->obj[pt_btn]);
	disable_button(gui, gui->obj[rt_btn]);
	disable_button(gui, gui->obj[rm_btn]);
//	disable_button(gui, rt_btn);
//	disable_button(gui, rt_btn);
//	disable_button(gui, rm_btn);

	activate_button(gui, btn);
	SDL_UpdateWindowSurface(g_sdl.win_tool);
}

void		callback_on_click(union SDL_Event event, void * data)
{
	//todo add callback function
}
