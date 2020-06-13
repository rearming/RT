/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_text_box_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"
#include "rt.h"

void			auto_init_btns(SDL_Rect rect, short action, char *text,
		float param)
{
	const SDL_Color color = get_color_from_hex(BTN_COLOR_CLICK);

	sprintf(g_gui.obj[action].field, "%i", (int)(param));
	g_gui.obj[action].rect = rect;
	g_gui.obj[action].action = action;
	g_gui.obj[action].callback = button_callback;
	g_gui.obj[action].state = hidden;
	if (action >= c_pos_x && action <= c_angle_z)
		g_gui.obj[action].type = CAM_TEXT_BOX;
	else
		rt_raise_error(PANEL_BOXES_TROUBLE);
	g_gui.obj[action].color = color;
	g_gui.obj[action].focus = 0;
	ft_strcpy(g_gui.obj[action].text, text);
}

t_transform		auto_init_btns_ret(SDL_Rect rect, short action, char *text,
								float param)
{
	const SDL_Color	color = get_color_from_hex(BTN_COLOR_CLICK);
	t_transform		btn;

	ft_sprintf(&(btn.field), "%i", (int)(param));
	btn.rect = rect;
	btn.action = action;
	btn.callback = button_callback;
	btn.state = hidden;
	if (action >= c_pos_x && action <= c_angle_z)
		btn.type = CAM_TEXT_BOX;
	else
		rt_raise_error(PANEL_BOXES_TROUBLE);
	btn.color = color;
	btn.focus = 0;
	ft_strcpy(btn.text, text);
	return (btn);
}
