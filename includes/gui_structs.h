#ifndef GUI_STRUCTS_H
#define GUI_STRUCTS_H


/*
** SDL_gui structs
*/

typedef	struct			s_transform
{
	SDL_Rect			rect;
	SDL_Color			color;
	SDL_Color			rise_btn;
	SDL_Surface			texture;
	char				*text;
	void				*callback;
	void				*parent;
	bool				state;
}						t_transform;

typedef enum			e_button
{
						pt_btn,
						rt_btn,
						rm_btn
}						t_btn;

typedef struct			s_gui
{
						//TODO: optimise this
	t_transform			*obj[100];
	TTF_Font			*font;
	SDL_Surface			*surface;

}						t_gui;

#endif //GUI_STRUCTS_H
