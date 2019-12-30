#include "rt.h"

void		rt_render(t_rt *rt, void (*render_func)(t_rt *))
{
	SDL_LockTexture(g_sdl.texture, 0,
			(void**)&g_img_data, &g_sdl.pitch);
	render_func(rt);
	SDL_UnlockTexture(g_sdl.texture);
	SDL_SetRenderTarget(g_sdl.rend, g_sdl.texture);
	SDL_RenderCopy(g_sdl.rend, g_sdl.texture, NULL, NULL);
	SDL_RenderPresent(g_sdl.rend);
}
