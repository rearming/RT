#include "rt.h"

void		rt_render(void *rt_ptr, void (*render_func)(void *))
{
	SDL_LockTexture(g_sdl.texture, 0,
			(void**)&g_img_data, &g_sdl.pitch);
	render_func(rt_ptr);
	SDL_UnlockTexture(g_sdl.texture);
	SDL_SetRenderTarget(g_sdl.rend, g_sdl.texture);
	SDL_RenderCopy(g_sdl.rend, g_sdl.texture, NULL, NULL);
	SDL_RenderPresent(g_sdl.rend);
}
