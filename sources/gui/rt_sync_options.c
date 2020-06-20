/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sync_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:51:44 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/20 17:55:43 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"

void	sync_options_buttons(uint64_t options, u_int64_t states)
{
	int i;

	i = msh_btn;
	while (i <= sb_btn)
	{
		if (g_gui.obj[i].state != hover)
			g_gui.obj[i].state = (options & g_gui.obj[i].bit) ?
		(click) : (non_event);
		i++;
	}
	while (i <= tunes_btn)
	{
		if (g_gui.obj[i].state != hover)
			g_gui.obj[i].state = (states & g_gui.obj[i].bit) ?
		(click) : (non_event);
		i++;
	}
}
