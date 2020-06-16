/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_button_callback.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"
#include "rt.h"

bool		handle_button(t_transform *btn, t_rt *rt)
{
	if (btn->type & RENDER_BTN)
	{
		btn->state = click;
		change_render_algo(btn->action, rt);
		g_gui.render_algo = btn->action;
		return (true);
	}
	else if (btn->type & SCREENSHOT)
	{
		if (SCREENSHOT_FORMAT == BMP)
			create_screenshot_bmp();
		else if (SCREENSHOT_FORMAT == JPG)
			create_screenshot_jpg();
		else
			create_screenshot_png();
		return (true);
	}
	else if (btn->type & PANEL)
	{
		btn->state = click;
		g_gui.panel = btn->action;
		return (true);
	}
	return (false);
}

bool		handle_textbox(t_transform *btn, SDL_Event *event)
{
	if (event->type == SDL_MOUSEMOTION)
		return (false);
	if (event->type == SDL_MOUSEBUTTONDOWN && check_click(event, btn->rect))
	{
		btn->focus = true;
		return (true);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN && btn->focus &&
		!check_click(event, btn->rect))
	{
		btn->focus = false;
		return (true);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN && check_hover(event, btn->rect))
	{
		return (true);
	}
	return (false);
}



bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt)
{
	if (btn->type & TEXT_BOX)
	{
		return (handle_textbox(btn, event));
	}
	if (event->type != SDL_MOUSEBUTTONDOWN && event->type != SDL_MOUSEMOTION)
		return (false);
	if (event->type == SDL_MOUSEMOTION && check_hover(event, btn->rect) &&
		btn->state != click)
	{
		btn->state = hover;
		return (true);
	}
	if (event->type == SDL_MOUSEMOTION && !check_hover(event, btn->rect) &&
		btn->state == hover)
	{
		btn->state = non_event;
		return (true);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN && btn->state == hover &&
		check_click(event, btn->rect))
		return (handle_button(btn, rt));
	return (false);
}
