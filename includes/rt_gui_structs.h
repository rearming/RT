/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GUI_STRUCTS_H
# define RT_GUI_STRUCTS_H

/*
** SDL_gui structs
*/

typedef enum			e_button
{
	rt_btn,
	pt_btn,
	scr_sbtn,
	camera_l,
	c_pos_x,
	c_pos_y,
	c_pos_z,
	c_angle_x,
	c_angle_y,
	c_angle_z,
	msh_btn,
	obj_btn,
	texture_btn,
	aa_btn,
	sb_btn,
	imp_btn,
	blur_btn,
	sepia_btn,
	tunes_btn,
	btn_count
}						t_btn;

typedef enum			e_state
{
	non_event,
	hover,
	click,
	label,
	hidden
}						t_state;

typedef	struct			s_transform
{
	SDL_Rect			rect;
	SDL_Color			color;
	SDL_Surface			texture;
	char				text[100];
	char				*field;
	t_btn				action;
	bool				(*callback)();
	t_state				state;
	uint16_t			type;
	bool				focus;
	float				param;
	uint32_t			bit;
}						t_transform;

typedef struct			s_ttf
{
	SDL_Surface			*surface;
	SDL_Color			color;
	SDL_Rect			rect;
}						t_ttf;

typedef struct			s_gui
{
	SDL_Window			*win_tool;
	t_transform			*obj;
	TTF_Font			*subtitle;
	TTF_Font			*title;
	TTF_Font			*body;
	SDL_Surface			*surface;
	enum e_button		render_algo;
	enum e_button		panel;
}						t_gui;

#endif
