/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_render_callback.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 18:52:27 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/20 15:55:31 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gui.h"
#include "rt.h"

bool		check_hover(SDL_Event *event, SDL_Rect button)
{
	if (event->motion.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h))
		return (true);
	return (false);
}

bool		check_click(SDL_Event *event, SDL_Rect button)
{
	if (event->button.x > button.x && event->button.y > button.y &&
		event->button.x < (button.x + button.w) &&
		event->button.y < (button.y + button.h))
		return (click);
	return (false);
}

void		create_screenshot(void)
{
	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	SDL_Surface *surface;
	static int postfix;
	char *file;

	if (!postfix)
		postfix = 1;
	surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels, surface->pitch);
	file = ft_strjoin(ft_strjoin("Screenshot", ft_itoa(postfix)), ".bmp");
	postfix++;
	SDL_SaveBMP(surface, file);
	free(file);
	SDL_FreeSurface(surface);
}

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
		create_screenshot();
		return (true);
	}
	return (false);
}

bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt)
{

	if (event->type != SDL_MOUSEBUTTONDOWN && event->type != SDL_MOUSEMOTION)
		return (false);
	if (event->type == SDL_MOUSEMOTION && check_hover(event, btn->rect) && btn->state != click)
	{
		btn->state = hover;
		return (true);
	}
	if (event->type == SDL_MOUSEMOTION && !check_hover(event, btn->rect) && btn->state == hover)
	{
		btn->state = non_event;
		return (true);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN && btn->state == hover && check_click(event, btn->rect))
		return (handle_button(btn, rt));
	return (false);
}