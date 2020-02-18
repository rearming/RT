#ifndef GUI_STRUCTS_H
#define GUI_STRUCTS_H

#include "gui_defines.h"
/*
** SDL_gui structs
*/

typedef	struct			s_transform
{
	SDL_Rect			rect;
	SDL_Color			color;
	SDL_Surface			texture;
	char				*text;
	short 				action;
	bool				(*callback)();
	void				*parent;
	bool				state;
	short				type;
}						t_transform;

typedef enum			e_button
{
						pt_btn,
						rt_btn,
//						rm_btn
						btn_count
}						t_btn;

typedef struct			s_gui
{
						//TODO: optimise this
//	t_transform			obj[TRANSFORM_COUNT];
	t_transform			*obj;
	TTF_Font			*font;
	SDL_Surface			*surface;

}						t_gui;

#endif //GUI_STRUCTS_H
