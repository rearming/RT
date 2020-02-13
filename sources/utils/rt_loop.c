#include "rt.h"
#include "../debug/rt_debug_utils.h"




void		rt_loop(t_rt *rt)
{
//	union nkc_event			nk_event;
	SDL_Event		event;
//	t_nk_main		nk;


	SDL_SetRelativeMouseMode(SDL_TRUE);
	bool flag = false;

	while (21 || 42)
	{
		while (SDL_PollEvent(&event))
		{
			handle_event(&event, rt);

//			nk_event = nkc_poll_events(nk.myapp.nkcHandle);
		}
		rt_render(rt, rt_opencl_render);
//		nk_render();
		if (flag == true)
		{
			rt_pathtrace_profile(rt, 1000);
			flag = false;
		}
		if (event.type == SDL_QUIT)
//		|| (nk_event.type == NKC_EWINDOW) && (nk_event.window.param == NKC_EQUIT))
			break ;
	}
}

