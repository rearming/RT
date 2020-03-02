#ifndef RT_GUI_STRUCTS_H
#define RT_GUI_STRUCTS_H


/*
** SDL_gui structs
*/



typedef enum			e_button
{
						rt_btn,
						pt_btn,
//						rm_btn
						algo_btn_count,
						scr_sbtn = 0,
//						test_btn,
						other_btn_count,
						btn_count = algo_btn_count + other_btn_count
}						t_btn;

typedef enum 			e_state
{
						non_event,
						hover,
						click,
						label
}						t_state;

typedef	struct			s_transform
{
	SDL_Rect			rect;
	SDL_Color			color;
	SDL_Surface			texture;
	char				text[100];
	short				action;
	bool				(*callback)();
	t_state 			state;
	short				type;
	void				*parent;
	unsigned short		sons;
}						t_transform;

typedef struct			s_gui
{
	SDL_Window			*win_tool;
	t_transform			*obj;
	TTF_Font			*font;
	SDL_Surface			*surface;
	t_btn				render_algo;
}						t_gui;

#endif //RT_GUI_STRUCTS_H
