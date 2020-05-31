#ifndef RT_GUI_STRUCTS_H
# define RT_GUI_STRUCTS_H

/*
** SDL_gui structs
*/

typedef enum			e_button
{
	rt_btn,
	pt_btn,
//						rm_btn,
//						meshes,
	scr_sbtn,
	camera_l,
//	obj_pos,
//	obj_param,
	c_pos_x,
	c_pos_y,
	c_pos_z,
	c_angle_x,
	c_angle_y,
	c_angle_z,
//	obj_pos_x,
//	obj_pos_y,
//	obj_pos_z,
//	obj_angle_x,
//	obj_angle_y,
//	obj_angle_z,
//	param_pos_x,
//	param_pos_y,
//	param_pos_z,
//	param_angle_x,
//	param_angle_y,
//	param_angle_z,
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
//	char				field[10];
	char*				field;
	short				action;
	bool				(*callback)();
	t_state				state;
	short				type;
	bool				focus;
	float 				param;
//	void				*parent;
//	unsigned short		sons;
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

#endif //RT_GUI_STRUCTS_H
