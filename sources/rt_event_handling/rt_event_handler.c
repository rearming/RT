#include "rt.h"

void		handle_event(SDL_Event *event, t_rt *rt)
{
	RT_UNUSED(rt);
	if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(rt_exit_clean());
}
