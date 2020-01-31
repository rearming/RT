#include "rt.h"
#include "rt_events.h"

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

static inline bool	any_key_pressed(t_events *events)
{
	return (events->w || events->a || events->s || events->d
			|| events->space || events->lshift);
}

static inline void		rt_handle_keypress(SDL_Event *event, t_rt *rt)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(rt_exit_clean());
	if (event->key.keysym.scancode == SDL_SCANCODE_I)
		rt->events.info = !rt->events.info;
	if (event->key.keysym.scancode == SDL_SCANCODE_M)
		SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
	if (event->key.keysym.scancode == SDL_SCANCODE_R)
	{
		rt->opencl_params.render_algo = RAY_TRACE;
		rt_render(rt, &rt_opencl_render);
	}
	if (event->key.keysym.scancode == SDL_SCANCODE_P)
		rt->opencl_params.render_algo = PATH_TRACE;
	if (event->key.keysym.scancode == SDL_SCANCODE_N)
		rt_render(rt, &rt_opencl_render);
}

void		handle_event(SDL_Event *event, t_rt *rt)
{
	if (event->type == SDL_KEYUP)
		remove_key_event(&rt->events, event->key.keysym.scancode);
	else if (event->type == SDL_KEYDOWN)
	{
		rt_handle_keypress(event, rt);
		rt_add_key_event(&rt->events, event->key.keysym.scancode);
	}
	else if (event->type == SDL_MOUSEMOTION && SDL_GetRelativeMouseMode())
	{
		rt->scene.camera.rotation.x -=
				event->motion.yrel * ROTATION_SPEED * WIN_RATIO;
		rt->scene.camera.rotation.y += event->motion.xrel * ROTATION_SPEED;
	}
	if (any_key_pressed(&rt->events)
	|| event->type == SDL_MOUSEMOTION
	|| rt->opencl_params.render_algo == PATH_TRACE)
	{
		rt_camera_move(&rt->scene.camera, &rt->events);
		rt_render(rt, &rt_opencl_render);
	}
}
