#include "test_header.h"

void	test_event_loop(void (*func)(void*), void *ptr)
{
	SDL_Event	event;

	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				exit(EXIT_SUCCESS);
			if (func)
				func(ptr);
		}
		if (event.type == SDL_QUIT)
			break ;
	}
}
