/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text_box.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"

float		count_percent(char *text)
{
//	const size_t joined_len = ft_strlen(text) + 5;
//	const size_t text_len = ft_strlen(text);

	return (0.6);
}

void		render_text_box(t_transform btn)
{
	SDL_Rect	text;
	SDL_Rect	field;
	SDL_Color	color;

	if (btn.state == hidden)
		return ;
	if (btn.focus == true)
		color = get_color_from_hex(TEXT_BOX_FOCUSED);
	else
		color = get_color_from_hex(TEXT_BOX_UNFOCUSED);
	render_rect(g_gui.surface, &(btn.rect), color);
	text = (SDL_Rect){.x = btn.rect.x, .y = btn.rect.y, .h = btn.rect.h};
	text.w = (int)((float)btn.rect.w) * 0.6;// * count_percent(btn.text));
	field = (SDL_Rect){.x = btn.rect.x + text.w,
					.y = btn.rect.y, .h = btn.rect.h};
	field.w = btn.rect.w - text.w;
	render_text(g_gui.body, btn.text, text);
	render_text(g_gui.body, btn.field, field);
}
