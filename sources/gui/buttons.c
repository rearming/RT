/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:41 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/15 17:45:56 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

bool		check_button(SDL_Event *event, SDL_Rect button)
{
	if (event->button.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h))
		return (true);
	return (false);
}

void		render_button(t_gui *gui, t_transform btn)
{
	SDL_FillRect(gui->surface,
			&(btn.rect),
			SDL_MapRGBA(
					gui->surface->format,
					btn.color.r,
					btn.color.g,
					btn.color.b,
					btn.color.a
			));
}

void		activate_button(t_gui *gui, t_transform *btn)
{
	if (btn->state)
		return;
	btn->state = true;
	btn->color = activate_color(btn->color);
	render_button(gui, *btn);
}

void		disable_button(t_gui *gui, t_transform *btn)
{
	if (!btn->state)
		return;
	btn->state = false;
	btn->color = disable_color(btn->color);
	render_button(gui, *btn);
}

