#include "rt.h"
#include "rt_events.h"
#include "gui.h"

static inline void		rt_add_key_event(t_events *events, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		events->w = TRUE;
	if (scancode == SDL_SCANCODE_S)
		events->s = TRUE;
	if (scancode == SDL_SCANCODE_A)
		events->a = TRUE;
	if (scancode == SDL_SCANCODE_D)
		events->d = TRUE;
	if (scancode == SDL_SCANCODE_SPACE)
		events->space = TRUE;
	if (scancode == SDL_SCANCODE_X)
		events->lshift = TRUE;
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
		rt->opencl_params.render_algo = RAY_TRACE;
	if (event->key.keysym.scancode == SDL_SCANCODE_P)
		rt->opencl_params.render_algo = PATH_TRACE;
	if (event->key.keysym.scancode == SDL_SCANCODE_N)
		rt_render(rt, &rt_opencl_render);
}

//void		handle_mouse(SDL_Event *event, t_rt *rt)//todo : change to new architecture
//{
//	if (event->button.button == SDL_BUTTON_LEFT)
//	{
//		g_sdl.surface = SDL_GetWindowSurface(g_sdl.win_tool);
//
//		if (check_button(event, g_sdl.buttons[pt_btn].button))
//		{
//			rt->opencl_params.render_algo = PATH_TRACE;
//			switch_render_algo(PATH_TRACE, pt_btn, rt);
//
//		}
//		else if (check_button(event, g_sdl.buttons[rt_btn].button))
//		{
//			rt->opencl_params.render_algo = RAY_TRACE;
//			switch_render_algo(RAY_TRACE, rt_btn, rt);
//		}
//		else if (check_button(event, g_sdl.buttons[rm_btn].button))
//		{
//			switch_render_algo(RAY_TRACE, rm_btn, rt);
//		}
//
//		SDL_UpdateWindowSurface(g_sdl.win_tool);
//	}
//}

void		handle_mouse(SDL_Event *event, t_rt *rt, t_gui *gui)
{
	printf("checking rectangle %i %i\n", gui->obj[pt_btn].rect.w, gui->obj[pt_btn].rect.h);
	printf("поймана крыса position x: %i y:%i; intersect%i\n", event->button.x, event->button.x, check_button(event, gui->obj[pt_btn].rect));
	gui->surface = SDL_GetWindowSurface(g_sdl.win_tool);
	if (check_button(event, gui->obj[pt_btn].rect))
	{
		printf("ебать, работаем\n");
	}
}


void		handle_mouse_g(SDL_Event *event, t_rt *rt)
{
	g_gui.surface = SDL_GetWindowSurface(g_sdl.win_tool);
	if (check_button(event, g_gui.obj[pt_btn].rect))
	{
		printf("ебать, работаем\n");
//		g_gui.obj[pt_btn].callback(pt_btn, (void *)rt);
//		g_gui.obj[pt_btn].callback;//todo: разобраться с callback function

	}
}

void		handle_event(SDL_Event *event, t_rt *rt, t_gui *gui)
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
	else if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		handle_mouse(event, rt, gui);
	}
	if (any_key_pressed(&rt->events)
	|| event->type == SDL_MOUSEMOTION
	|| rt->opencl_params.render_algo == PATH_TRACE)
	{
		rt_camera_move(&rt->scene.camera, &rt->events);
		rt_render(rt, &rt_opencl_render);
	}
}

void		handle_event_g(SDL_Event *event, t_rt *rt)
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
	else if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		handle_mouse_g(event, rt);
	}
	if (any_key_pressed(&rt->events)
		|| event->type == SDL_MOUSEMOTION
		|| rt->opencl_params.render_algo == PATH_TRACE)
	{
		rt_camera_move(&rt->scene.camera, &rt->events);
		rt_render(rt, &rt_opencl_render);
	}
}
