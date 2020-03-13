#include "rt.h"
#include "rt_debug.h"
#include "rt_opencl.h"

void		rt_loop(t_rt *rt)
{
	SDL_Event		event;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	bool flag = false;

	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			handle_event(&event, rt);
//#ifndef __APPLE__
			SDL_FlushEvent(SDL_MOUSEMOTION);
//#endif
		}
		if (rt_params_isset(rt->render_settings, RENDER_PATHTRACE))
			rt_render(rt, render_wavefront);
		if (flag == true)
		{
			rt_pathtrace_profile(rt, 1000);
			flag = false;
		}
		if (event.type == SDL_QUIT)
			break ;
	}
}

