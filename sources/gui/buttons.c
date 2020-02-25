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
		return (true);
	return (false);
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
					color.a));
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

void		create_screenshot(t_rt *rt)
{
	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	SDL_Surface *surface;
	static int postfix;
	char *file;

	if (!postfix)
		postfix = 1;
	surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32, format);
	SDL_RenderReadPixels(g_sdl.rend, NULL, format, surface->pixels, surface->pitch);
	if (postfix > 0)
		file = ft_strjoin(ft_strjoin("Screenshot", ft_itoa(postfix)), ".bmp");
	else
		file = ft_strjoin("Screenshot", ".bmp");
	postfix++;
	SDL_SaveBMP(surface, file);
	free(file);
}

bool		handle_button(t_transform *btn, t_rt *rt)
{
	if (btn->type & CHANGE_ALGO)
	{
		btn->state = click;
		change_render_algo(btn->action, rt);
		g_gui.render_algo = btn->action;
		return (true);
	}
	else if (btn->type & SCREENSHOT)
	{
		create_screenshot(rt);
	}
}

bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt)
{
	short	e_type;
	bool	state;

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		e_type = click;
		state = check_button(event, btn->rect);
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		e_type = hover;
		state = check_hover(event, btn->rect);
	}
	if (e_type == hover && state && btn->state != click)
	{
		btn->state = hover;
		return (true);
	}
	if (e_type == hover && !state && btn->state == hover)
	{
		btn->state = non_event;
		return (true);
	}
	if (e_type == click && btn->state == hover && state)
		return (handle_button(btn, rt));
	return (false);
}
