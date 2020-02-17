/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:51 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/17 22:38:13 by dgreat           ###   ########.fr       */
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

//void	resize_surface(SDL_Rect srcrect, SDL_Rect dstrect,
//					   SDL_Surface *texture)
//{
//	SDL_BlitScaled(texture, NULL, g_sdl.surface, &dstrect);
//}
//
//void				render_surface(SDL_Rect srcrect, SDL_Rect dstrect)
//{
//	SDL_Surface		*copy_texture;
//
//	copy_texture = SDL_DuplicateSurface(g_sdl.surface);
//	resize_surface(srcrect,
//				   dstrect,
//				   copy_texture);
//	SDL_BlitSurface(g_sdl.surface, NULL, copy_texture, NULL);
//	SDL_FreeSurface(copy_texture);
//}

//SDL_BlitSurface(text, &((SDL_Rect){ -8 , -8 ,100, 30 }), button.surface, NULL);
//SDL_BlitSurface(text, &((SDL_Rect){ -8 , -8 ,100, 30 }), button.pressed, NULL);

void		call_test(int render, void *rt_)
{

	t_rt *rt;

	rt = (t_rt *)rt_;
	rt->opencl_params.render_algo = render - 1;
}


t_gui		*init_gui(void)
{
	t_gui		gui;
	SDL_Rect	rect;

	TTF_Init();
	gui.font = TTF_OpenFont("./Fonts/Techno.ttf", FONT_SIZE);
	gui.surface = SDL_GetWindowSurface(g_sdl.win_tool);
	SDL_FillRect(gui.surface, NULL,
				 SDL_MapRGB(gui.surface->format, 63, 63, 63));
	rect = (SDL_Rect){.x = 0, .y = 0, .h = 100, .w = WIN_GUI_WIDTH / 3} ;
	gui.obj[pt_btn] = create_gui_obj(rect, COL_RED, "Path trace", call_test);
//	gui.obj[pt_btn] = create_gui_obj(rect, COL_RED, NULL, NULL);
	activate_button(gui.obj[pt_btn]);
	SDL_UpdateWindowSurface(g_sdl.win_tool);
	return (&gui);
}

void		init_gui_g(void)
{

	SDL_Rect	rect;

	TTF_Init();
	g_gui.font = TTF_OpenFont("./Fonts/Techno.ttf", FONT_SIZE);
	g_gui.surface = SDL_GetWindowSurface(g_sdl.win_tool);
	SDL_FillRect(g_gui.surface, NULL,
				 SDL_MapRGB(g_gui.surface->format, 63, 63, 63));
	rect = (SDL_Rect){.x = 0, .y = 30, .h = 100, .w = WIN_GUI_WIDTH / 2};
	g_gui.obj[pt_btn] = create_gui_obj(rect, COL_RED, "Path trace", call_test);
	rect.x += WIN_GUI_WIDTH / 2;
	g_gui.obj[rt_btn] = create_gui_obj(rect, COL_RED, "Ray trace", call_test);
//	g_gui.obj[pt_btn] = create_g_gui_obj(rect, COL_RED, NULL, NULL);
	activate_button(g_gui.obj[pt_btn]);
	SDL_UpdateWindowSurface(g_sdl.win_tool);
}
