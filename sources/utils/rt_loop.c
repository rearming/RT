#include "rt.h"

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
//		if (rt->opencl_params.render_algo == PATH_TRACE)
//			rt_render(rt, &rt_opencl_render);
		if (event.type == SDL_QUIT)
			break ;
	}
}

