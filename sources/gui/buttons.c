/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:41 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/17 22:38:30 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

bool		check_button(SDL_Event *event, SDL_Rect button)
{
	if (event->button.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h))
		return (true);
	return (false);
}

void		render_text(t_gui *gui)
{

}

void		render_button(t_transform btn)
{
	SDL_Surface *text_surface;

	text_surface = TTF_RenderText_Blended(g_gui.font, btn.text, btn.color);
	SDL_BlitSurface(text_surface, &btn.rect, g_gui.surface, NULL);
	SDL_FillRect(g_gui.surface,
			&(btn.rect),
			SDL_MapRGBA(
					g_gui.surface->format,
					btn.color.r,
					btn.color.g,
					btn.color.b,
					btn.color.a
			));
//			SDL_MapRGB(
//					gui->surface->format,
//					btn.color.r,
//					btn.color.g,
//					btn.color.b
//			));

//	SDL_BlitSurface(text_surface, &btn.rect, gui->surface, NULL);

}

void		activate_button(t_transform btn)
{
	if (btn.state)
		return;
	btn.state = true;
	btn.color = activate_color(btn.color);
	render_button(btn);
}

void		disable_button(t_transform btn)
{
	if (!btn.state)
		return;
	btn.state = false;
	btn.color = disable_color(btn.color);
	render_button(btn);
}

