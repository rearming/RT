/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:41 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/20 15:55:31 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "rt.h"

bool		check_hover(SDL_Event *event, SDL_Rect button)
{
	if (event->motion.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h))
		return true;
	return false;
}

bool		check_button(SDL_Event *event, SDL_Rect button)
{
	if (event->button.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h))
		return (click);
	return (false);
}

void		render_button(t_transform btn)
{
	SDL_Surface *text_surface;
	SDL_Color	color;

	text_surface = TTF_RenderText_Solid(g_gui.font, btn.text,
			(SDL_Color){255, 255, 255, 255});
	if (btn.state == click)
		color = get_color_from_hex(BTN_COLOR_CLICK);
	else if (btn.state == hover)
		color = get_color_from_hex(BTN_COLOR_HOVER);
	else
		color = get_color_from_hex(BTN_COLOR_NONACTIVE);
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

void		update_all_algo_buttons(void)
{
	int	j;

	j = 0;
	while (j < algo_btn_count)
	{
		if (g_gui.obj[j].action != g_gui.render_algo)
		{
			g_gui.obj[j].state = non_event;
			render_button(g_gui.obj[j]);
		}
		j++;
	}

}