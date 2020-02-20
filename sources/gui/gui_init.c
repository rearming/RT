/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:51 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/20 15:55:11 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

t_transform	create_gui_obj(
		SDL_Rect		button,
		unsigned int	color,
		char			*text,
		void			*callback)
{
	t_transform		gui_obj;

	gui_obj.rect = button;
	gui_obj.color = get_color_from_hex(color);
	if (text != NULL)
		gui_obj.text = ft_strdup(text);
	else
		gui_obj.text = NULL;
	gui_obj.callback = callback;
	return (gui_obj);
}

void		change_render_algo(short algo, t_rt *rt)
{
	rt->opencl_params.render_algo = algo + 1;
}

bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt)
{

//	if (check_button(event, btn->rect))
//	{
//		if (btn->type & CHANGE_ALGO)
//		{
//			change_render_algo(btn->action, rt);
//			btn->state = !btn->state;
//		}
//		return (true);
//	}
//	return (false);

	short e_type;
	if (event->type == SDL_MOUSEBUTTONDOWN)
		e_type = click;
	else if (event->type == SDL_MOUSEMOTION)
		e_type = hover;

	if (btn->type & CHANGE_ALGO)
	{
		if (btn->state != click)
		{
			if (e_type == click && check_button(event, btn->rect))
			{
				change_render_algo(btn->action, rt);
				btn->state = click;
			}
			else if (e_type == hover && check_hover(event, btn->rect))
			{
				btn->state = hover;
			}
		}
		else if (btn->state != click && btn->state != hover)
			btn->state = non_event;
		return (true);
	}
	return (false);
}

void		init_gui(void)
{
	int			i;
	SDL_Rect	rect;

	TTF_Init();
	g_gui.obj = rt_safe_malloc(sizeof(t_transform) * btn_count);
	g_gui.font = TTF_OpenFont("./Fonts/Techno.ttf", FONT_SIZE);
	g_gui.surface = SDL_GetWindowSurface(g_sdl.win_tool);
	SDL_FillRect(g_gui.surface, NULL,
			SDL_MapRGB(g_gui.surface->format, 63, 63, 63));
	rect = (SDL_Rect){.x = 0, .y = 30, .h = 100, .w = WIN_GUI_WIDTH / 2};
	g_gui.obj[pt_btn] = (t_transform){ .rect = rect, .state = 0 ,
		.text = "Path trace", .callback = button_callback, .action = pt_btn,
		.type = RENDER_BTN, .color = get_color_from_hex(COL_RED)};
	rect.x += WIN_GUI_WIDTH / 2;
	g_gui.obj[rt_btn] = (t_transform){ .rect = rect, .state = 1,
		.text = "Ray trace", .callback = button_callback, .action = rt_btn,
		.type = RENDER_BTN, .color = get_color_from_hex(COL_BLUE)};

	i = 0;
	while (i < btn_count)
		render_button(g_gui.obj[i++]);

	SDL_UpdateWindowSurface(g_sdl.win_tool);
}
