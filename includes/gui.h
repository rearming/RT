
#ifndef GUI_H
#define GUI_H

# include <SDL.h>
# include <SDL_ttf.h>

//#endif

# include <stdbool.h>

# include "gui_defines.h"
# include "gui_errors.h"
# include "gui_structs.h"



void		init_gui(short algo);

/*
** Buttons
*/

bool		check_button(SDL_Event *event, SDL_Rect button);

bool		check_hover(SDL_Event *event, SDL_Rect button);

void		render_button(t_transform btn);

void		update_all_buttons(void);

void		update_all_algo_buttons(void);


/*
** Utils
*/

SDL_Color	get_color_from_hex(unsigned int hex);

SDL_Color	get_rgba_from_hex(unsigned int hex);

SDL_Color activate_color(SDL_Color color);

SDL_Color disable_color(SDL_Color color);

//bool		button_callback(t_transform *btn, SDL_Event *event, t_rt *rt);

#endif //GUI_H
