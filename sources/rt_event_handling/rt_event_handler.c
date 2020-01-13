#include "rt.h"

void		handle_event(SDL_Event *event, t_rt *rt)
{
	RT_UNUSED(rt);
	if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(rt_exit_clean());
	if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
		rt_render(rt, &rt_opencl_render);
}
