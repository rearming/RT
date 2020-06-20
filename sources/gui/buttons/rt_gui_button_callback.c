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

bool		gui_switch_bit(uint32_t *options, t_transform *btn,
		SDL_Event *event)
{
	t_state tmp;

	tmp = btn->state;
	rt_switch_bit(options, btn->bit);
	btn->state = (*options & btn->bit) ? (click) : (non_event);
	if (tmp == btn->state)
		return (true);
	return (false);
}

bool		handle_option(t_transform *btn, SDL_Event *event, t_rt *rt)
{
	if (check_click(event, btn->rect) && event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (btn->type & OPTION_BTN)
			return (gui_switch_bit(&rt->render_options, btn, event));
		else if (btn->type & STATE_BTN)
			return (gui_switch_bit(&rt->render_state, btn, event));
		return (true);
	}
	if (check_hover(event, btn->rect) && event->type == SDL_MOUSEMOTION)
	{
		btn->state = hover;
		return (true);
	}
	if (!check_hover(event, btn->rect) && btn->state == hover)
	{
		if (btn->type & OPTION_BTN)
			btn->state = (rt->render_options & btn->bit) ? (click)
					: (non_event);
		else if (btn->type & STATE_BTN)
			btn->state = (rt->render_state & btn->bit) ? (click) : (non_event);
		return (true);
	}
	return (false);
}

bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt)
{
	bool res;

	res = false;
	if (btn->type & TEXT_BOX)
		res |= handle_textbox(btn, event);
	if (btn->type & (OPTION_BTN | STATE_BTN))
		return (handle_option(btn, event, rt));
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
	if (event->type == SDL_MOUSEBUTTONDOWN &&
		check_click(event, btn->rect))
	{
		printf("я нажал PATHTRACE\n");
		return (handle_button(btn, rt)); }
	return (false | res);
}

