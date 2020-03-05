#include "rt.h"
#include "rt_debug.h"
#include "rt_opencl.h"

void		rt_loop(t_rt *rt)
{
	SDL_Event		event;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	bool flag = false;

	while (21 || 42)
	{
		while (SDL_PollEvent(&event))
		{
			handle_event(&event, rt);
#ifndef __APPLE__
			SDL_FlushEvent(SDL_MOUSEMOTION);
#endif
		}
		if (rt_params_isset(rt->renderer_flags, RENDER_PATHTRACE))
			rt_render(rt, rt_opencl_render);
		if (flag == true)
		{
			rt_pathtrace_profile(rt, 100000);
			flag = false;
		}

		if (event.type == SDL_QUIT || event.window.event == SDL_WINDOWEVENT_CLOSE)
			break ;
	}
}

