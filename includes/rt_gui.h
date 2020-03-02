
#ifndef RT_GUI_H
#define RT_GUI_H

# include <SDL.h>
# include <SDL_ttf.h>

# include <stdbool.h>

# include "rt_gui_defines.h"
# include "rt_gui_errors.h"
# include "rt_gui_structs.h"

typedef struct s_rt t_rt;
typedef struct s_sdl t_sdl;

void		update_all_algo_buttons(void);
bool		rt_handle_event_gui(SDL_Event *event, t_rt *rt);
void		init_gui(uint64_t algo);

/*
** Buttons
*/

SDL_Rect	centered_label( SDL_Rect button, SDL_Surface *sur);
void		render_border(t_transform *btn, int px, SDL_Color color);

void		render_button(t_transform btn);
void		render_button_without_border(t_transform btn);
void		render_button_without_centered(t_transform btn);
void		render_button_without_anything(t_transform btn);
void		update_all_algo_buttons(void);

bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt);

/*
** Utils
*/

void		change_render_algo(short algo, t_rt *rt);
SDL_Color	get_color_from_hex(unsigned int hex);
SDL_Color	get_rgba_from_hex(unsigned int hex);

#endif //RT_GUI_H
