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
						scr_sbtn,
//						all_btn,
						camera_l,
						obj_l,
						obj_pos,
						btn_count //= all_btn
}						t_btn;

//typedef enum 			e_all_btns

typedef enum 			e_state
{
						non_event,
						hover,
						click,
						label,
						surface
}						t_state;

typedef	struct			s_transform
{
	SDL_Rect			rect;
	SDL_Color			color;
	SDL_Surface			texture;
	char				text[100];
	char 				field;
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
	TTF_Font			*subtitle;
	TTF_Font			*title;
	TTF_Font			*body;
//	TTF_Font 			*swp;
	SDL_Surface			*surface;
	t_btn				render_algo;
	t_btn 				panel;
}						t_gui;

#endif //RT_GUI_STRUCTS_H
