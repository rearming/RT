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
		if (event.type == SDL_QUIT)
			break ;
	}
}

