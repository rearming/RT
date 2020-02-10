#include "rt.h"

static inline void		rt_add_key_event(t_events *events, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		events->w = true;
	if (scancode == SDL_SCANCODE_S)
		events->s = true;
	if (scancode == SDL_SCANCODE_A)
		events->a = true;
	if (scancode == SDL_SCANCODE_D)
		events->d = true;
	if (scancode == SDL_SCANCODE_SPACE)
		events->space = true;
	if (scancode == SDL_SCANCODE_X)
		events->lshift = true;
}

static inline void		remove_key_event(t_events *events, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		events->w = false;
	if (scancode == SDL_SCANCODE_S)
		events->s = false;
	if (scancode == SDL_SCANCODE_A)
		events->a = false;
	if (scancode == SDL_SCANCODE_D)
		events->d = false;
	if (scancode == SDL_SCANCODE_SPACE)
		events->space = false;
	if (scancode == SDL_SCANCODE_X)
		events->lshift = false;
}

static inline void		rt_handle_keypress(SDL_Event *event, t_rt *rt)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(rt_exit_clean());
	if (event->key.keysym.scancode == SDL_SCANCODE_I)
		rt->events.info = !rt->events.info;
	if (event->key.keysym.scancode == SDL_SCANCODE_N)
		SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
	if (event->key.keysym.scancode == SDL_SCANCODE_R)
		rt_set_render_algo(&rt->renderer_flags, RENDER_RAYTRACE);
	if (event->key.keysym.scancode == SDL_SCANCODE_P)
		rt_set_render_algo(&rt->renderer_flags, RENDER_PATHTRACE);
	if (event->key.keysym.scancode == SDL_SCANCODE_M)
		rt_switch_render_param(&rt->renderer_flags, RENDER_MESH);
	if (event->key.keysym.scancode == SDL_SCANCODE_O)
		rt_switch_render_param(&rt->renderer_flags, RENDER_OBJECTS);
	if (event->key.keysym.scancode == SDL_SCANCODE_T)
		rt_switch_render_param(&rt->renderer_flags, RENDER_TEXTURES);
}

bool				rt_handle_key_event(SDL_Event *event, t_rt *rt)
{
	bool	event_handled;

	event_handled = false;
	if (event->type == SDL_KEYUP)
	{
		remove_key_event(&rt->events, event->key.keysym.scancode);
		event_handled = true;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		rt_handle_keypress(event, rt);
		rt_add_key_event(&rt->events, event->key.keysym.scancode);
		event_handled = true;
	}
	return (event_handled);
}
