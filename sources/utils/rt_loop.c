#include "rt.h"
#include "../debug/rt_debug_utils.h"

void		rt_loop(t_rt *rt)
{
	SDL_Event		event;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			handle_event(&event, rt);
		}
		rt_render(rt, rt_opencl_render);
//		return rt_pathtrace_profile(rt, 500);
		if (event.type == SDL_QUIT)
			break ;
	}
}

