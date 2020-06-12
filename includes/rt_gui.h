/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GUI_H
# define RT_GUI_H

# include <SDL.h>
# include <SDL_ttf.h>

# include <stdbool.h>

# include "rt_gui_defines.h"
# include "rt_gui_errors.h"
# include "rt_gui_structs.h"

typedef struct s_rt		t_rt;
typedef struct s_scene	t_scene;
typedef struct s_sdl	t_sdl;

void			init_gui(uint64_t algo, t_scene scene);
bool			rt_handle_event_gui(SDL_Event *event, t_rt *rt);

/*
** fake HTML
*/

t_ttf			get_centered_label(TTF_Font *font, char *text, SDL_Rect rect);
void			cut_rect(SDL_Rect *rect, int px);
void			render_border(t_transform *btn, int px, SDL_Color color);
void			render_text(TTF_Font *font, char *text, SDL_Rect rect);
void			render_rect(SDL_Surface *sur, SDL_Rect *rect, SDL_Color col);

/*
** Buttons init
*/

void			init_algo_buttons(void);
void			init_other_buttons(void);

/*
** Buttons render
*/

void			render_button(t_transform btn);
void			render_button_with_params(t_transform btn,
		TTF_Font *font, int px);
void			auto_render_button(int i);
void			fix_states(short action);

/*
** Buttons utils
*/

bool			check_click(SDL_Event *event, SDL_Rect button);
bool			check_hover(SDL_Event *event, SDL_Rect button);
void			render_all_buttons();

/*
** Buttons actions
*/

void			change_render_algo(short algo, t_rt *rt);
void			create_screenshot_bmp(void);
void			create_screenshot_png(void);
void			create_screenshot_jpg(void);
bool			button_callback(t_transform *btn, SDL_Event *event, t_rt *rt);

/*
** Text box init
*/

t_transform		auto_init_btns_ret(SDL_Rect rect, short action, char *text,
		float param);
void			auto_init_btns(SDL_Rect rect, short action, char *text,
		float param);
void			init_cam_text_box(t_scene scene, SDL_Rect rect);
void			init_pos_text_box(t_scene scene, SDL_Rect rect);
void			init_params_text_box(t_scene scene, SDL_Rect rect);
void			init_text_box(t_scene scene);

/*
** Text box render
*/

void			render_text_box(t_transform btn);

/*
** Utils
*/

bool			is_positions_changed(int tb_id, float curr_value);
char			*name_generator(char *ext);
SDL_Rect		get_window_data(void);
SDL_Color		get_color_from_hex(unsigned int hex);
SDL_Color		get_rgba_from_hex(unsigned int hex);

#endif
