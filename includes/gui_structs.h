#ifndef GUI_STRUCTS_H
#define GUI_STRUCTS_H


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
						algo_btn_count,
						scr_sbtn = 0,
						other_btn_count,
						btn_count = algo_btn_count + other_btn_count
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
	t_btn				render_algo;
}						t_gui;

#endif //GUI_STRUCTS_H
