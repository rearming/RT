/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:41 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/18 21:40:24 by dgreat           ###   ########.fr       */
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

void		render_button(t_transform btn)
{
	SDL_Surface *text_surface;
	SDL_Color	color;

	text_surface = TTF_RenderText_Solid(g_gui.font, btn.text,
			(SDL_Color){255, 255, 255, 255});
	if (!btn.state)
		color = disable_color(btn.color);
	else
		color = activate_color(btn.color);
	SDL_FillRect(g_gui.surface,
			&(btn.rect),
			SDL_MapRGBA(
					g_gui.surface->format,
					color.r,
					color.g,
					color.b,
					color.a
			));
	SDL_BlitSurface(text_surface, NULL, g_gui.surface, &btn.rect);

}

//void		activate_button(t_transform btn)
//{
//	if (btn.state)
//	{
//		render_button(btn);
//		return;
//	}
//	btn.state = true;
//	btn.color = activate_color(btn.color);
//	render_button(btn);
//}
//
//void		disable_button(t_transform btn)
//{
//	if (!btn.state)
//	{
//		render_button(btn);
//		return;
//	}
//	btn.state = false;
//	btn.color = disable_color(btn.color);
//	render_button(btn);
//}

