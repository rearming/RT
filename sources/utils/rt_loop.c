#include "rt.h"
#include "gui.h"
#include "../debug/rt_debug_utils.h"



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
		}
		rt_render(rt, rt_opencl_render);
		if (flag == true)
		{
			rt_pathtrace_profile(rt, 1000);
			flag = false;
		}
		if (event.type == SDL_QUIT)
			break ;
	}
}

