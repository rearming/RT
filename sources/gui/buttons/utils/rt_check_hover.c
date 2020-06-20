/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check_hover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"

bool		check_hover(SDL_Event *event, SDL_Rect button)
{
	if (event->window.windowID != GUI_WIN_ID)
		return (false);
	if (event->motion.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h) && !SDL_GetRelativeMouseMode())
		return (true);
	return (false);
}
