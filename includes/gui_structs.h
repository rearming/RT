#ifndef GUI_STRUCTS_H
#define GUI_STRUCTS_H

#include "gui_defines.h"
//#include "rt_structs.h"

/*
** SDL_gui structs
*/

typedef	struct			s_transform
{
	SDL_Rect			rect;
	SDL_Color			color;
	SDL_Surface			texture;
	char				*text;
	short				action;
	bool				(*callback)();
	void				*parent;
	short				state;
	short				type;
}						t_transform;

typedef enum			e_button
{
						pt_btn,
						rt_btn,
//						rm_btn
						btn_count
}						t_btn;

typedef enum 			e_event
{
						non_event,
						hover,
						click
}						t_event;

typedef struct			s_gui
{
	t_transform			*obj;
	TTF_Font			*font;
	SDL_Surface			*surface;
	t_btn				render;
}						t_gui;

#endif //GUI_STRUCTS_H
