/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:24:51 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/15 19:07:48 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

//SDL_Rect			button;
//struct SDL_Color	color;
//SDL_Surface			texture;
//char				*text;
//void				*callback;
//void				*parent;
//bool				active;



t_transform	*create_gui_obj(
		SDL_Rect		button,
		unsigned int	color,
		char			*text,
		void			*callback)
{
	t_transform		*gui_obj;

	gui_obj->rect = button;
	gui_obj->color = get_color_from_hex(color);
	gui_obj->text = ft_strdup(text);
	gui_obj->callback = callback;
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



void 		init_gui(void)
{
	t_gui gui;
//	gui_render_algo_buttons_init(3, 100);
	TTF_Init();
	g_sdl.surface = SDL_GetWindowSurface(g_sdl.win_tool);
	SDL_FillRect(g_sdl.surface, NULL,
			SDL_MapRGB(g_sdl.surface->format, 63, 63, 63));

	gui = (t_gui){.surface = SDL_GetWindowSurface(g_sdl.win_tool),
			.font = TTF_OpenFont("Fonts/Techno.ttf", FONT_SIZE)};

////	gui.obj[0]->rect = (SDL_Rect){.x = 0, .y = 0, .h = 50, .w = WIN_GUI_WIDTH};
//	gui.obj[1] = create_gui_obj((SDL_Rect){.x = 0, .y = 0, .h = 50, .w = WIN_GUI_WIDTH}, )
//	TTF_Font *font;
//	SDL_Color	clr;
//	SDL_Surface *text_box;

//	font = TTF_OpenFont("./Fonts/Techno.ttf", FONT_SIZE);

//	text_box = TTF_RenderText_Blended(font, "Path trace", clr);
//	render_surface((SDL_Rect){.x = 0, .y = 0,
//			.w = 0, .h = 0}, gui.obj[pt_btn]->rect);
	gui.obj[pt_btn]->rect = (SDL_Rect){.x = 0, .y = 0,
			.w = WIN_GUI_WIDTH / 3, .h = 100};
	gui.obj[pt_btn]->color = get_color_from_hex(COL_RED);
	SDL_Rect rect = gui.obj[pt_btn]->rect;
	gui.obj[pt_btn]->color = get_rgba_from_hex(0);
//	SDL_BlitSurface(text_box, NULL, g_sdl.surface, &rect);
	SDL_FillRect(g_sdl.surface, &gui.obj[pt_btn]->rect,
				SDL_MapRGB(g_sdl.surface->format, 255, 63, 63));
//	SDL_BlitSurface(text_box, NULL, g_sdl.surface, &gui.obj[pt_btn].rect);
//	text_box = TTF_RenderText_Blended(font, "Ray trace", clr);
//	SDL_BlitSurface(text_box, NULL, g_sdl.surface, &g_sdl.buttons[rt_btn].button);
//	text_box = TTF_RenderText_Blended(font, "Ray march", clr);
//	SDL_BlitSurface(text_box, NULL, g_sdl.surface, &g_sdl.buttons[rm_btn].button);
//	SDL_FreeSurface(text_box);
//	TTF_CloseFont(font);
	SDL_UpdateWindowSurface(g_sdl.win_tool);

}

t_gui		init_gui_s(void)
{
	t_gui		gui;
	SDL_Rect	rect;

	TTF_Init();
	gui.font = TTF_OpenFont("./Fonts/Techno.ttf", FONT_SIZE);
	gui.surface = SDL_GetWindowSurface(g_sdl.win_tool);
	SDL_FillRect(g_sdl.surface, NULL,
				 SDL_MapRGB(gui.surface->format, 63, 63, 63));
	rect = (SDL_Rect){.x = 0, .y = 0, .h = 100, .w = WIN_GUI_WIDTH / 3} ;
	gui.obj[pt_btn] = create_gui_obj(rect, COL_RED, "Path trace", NULL);
}
