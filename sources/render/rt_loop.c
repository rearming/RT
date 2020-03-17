#include "rt.h"
#include "rt_debug.h"
#include "rt_opencl.h"
#include "rt_events.h"

void		rt_loop(t_rt *rt)
{
	SDL_Event		event;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	bool flag = false;

	SDL_Event	events[MAX_EVENT_IN_LIST];
	int			event_num = 0;

	while (21)
	{
		while (SDL_PollEvent(&event) && event_num < MAX_EVENT_IN_LIST)
		{
			events[event_num] = event;
			event_num++;
		}
		handle_event(rt, events, event_num);
		event_num = 0;

		if (rt_bit_isset(rt->render_options, RENDER_PATHTRACE))
			rt_render(rt, rt_opencl_render);
		if (flag == true)
		{
			rt_pathtrace_profile(rt, 1000);
			flag = false;
		}

		if (event.type == SDL_QUIT || event.window.event == SDL_WINDOWEVENT_CLOSE)
			break ;
	}
}

