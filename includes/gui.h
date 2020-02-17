
#ifndef GUI_H
#define GUI_H

# include <SDL.h>
# include <SDL_ttf.h>

//#endif

# include <stdbool.h>

# include "gui_defines.h"
# include "gui_errors.h"
# include "gui_structs.h"

t_gui		*init_gui(void);

void		init_gui_g(void);

/*
** Buttons
*/

bool		check_button(SDL_Event *event, SDL_Rect button);

void		render_button(t_transform btn);

void		activate_button(t_transform btn);

void		disable_button(t_transform btn);


/*
** Utils
*/

SDL_Color	get_color_from_hex(unsigned int hex);

SDL_Color	get_rgba_from_hex(unsigned int hex);

SDL_Color activate_color(SDL_Color color);

SDL_Color disable_color(SDL_Color color);

//void		switch_render_algo(short algo, int btn, t_rt *rt, t_gui *gui);

void		callback_on_click(union SDL_Event event, void * data);

void		call_test(int render, void *rt_);

#endif //GUI_H
