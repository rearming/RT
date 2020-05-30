//#include <tclDecls.h>
#include "rt.h"
#include "rt_events.h"
#include "rt_gui.h"

static inline void		rt_add_key_event(uint32_t *events, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		rt_set_bit(events, EVENT_W);
	if (scancode == SDL_SCANCODE_S)
		rt_set_bit(events, EVENT_S);
	if (scancode == SDL_SCANCODE_A)
		rt_set_bit(events, EVENT_A);
	if (scancode == SDL_SCANCODE_D)
		rt_set_bit(events, EVENT_D);
	if (scancode == SDL_SCANCODE_SPACE)
		rt_set_bit(events, EVENT_SPACE);
	if (scancode == SDL_SCANCODE_X)
		rt_set_bit(events, EVENT_LSHIFT);
}

static inline void		remove_key_event(uint32_t *events, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		rt_unset_bit(events, EVENT_W);
	if (scancode == SDL_SCANCODE_S)
		rt_unset_bit(events, EVENT_S);
	if (scancode == SDL_SCANCODE_A)
		rt_unset_bit(events, EVENT_A);
	if (scancode == SDL_SCANCODE_D)
		rt_unset_bit(events, EVENT_D);
	if (scancode == SDL_SCANCODE_SPACE)
		rt_unset_bit(events, EVENT_SPACE);
	if (scancode == SDL_SCANCODE_X)
		rt_unset_bit(events, EVENT_LSHIFT);
}

void sync_rt_and_gui(t_scene scene, uint64_t renderer_params)
{
	const uint64_t	render_num = (renderer_params & (0b111)) - 1;

	g_gui.render_algo = render_num;
	g_gui.obj[render_num].state = click;
	render_button(g_gui.obj[render_num]);
	render_all_buttons(scene);
	SDL_UpdateWindowSurface(g_gui.win_tool);
}

static inline void		keypress_change_dof(SDL_Event *event, t_camera *camera)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
		camera->focal_distance -= camera->focal_distance > 0.5f ? 0.5f : 0.0f;
	if (event->key.keysym.scancode == SDL_SCANCODE_UP)
		camera->focal_distance += 0.5f;
	if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
		camera->aperture -= camera->aperture > 0.5f ? 0.5f : 0.0f;
	if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		camera->aperture += 0.5f;
	if (event->key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
		camera->blur_strength += 0.2f;
	if (event->key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
		camera->blur_strength -= camera->blur_strength > 0.5f ? 0.2f : 0;
}

static inline void		rt_handle_keypress(SDL_Event *event, t_rt *rt)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(rt_exit_clean());
	if (event->key.keysym.scancode == SDL_SCANCODE_I)
		rt_switch_bit(&rt->events, EVENT_INFO);
	if (event->key.keysym.scancode == SDL_SCANCODE_L)
		SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
	if (event->key.keysym.scancode == SDL_SCANCODE_R)
	{
		rt_set_render_algo(&rt->render_options, RENDER_RAYTRACE);
		sync_rt_and_gui(rt->scene, rt->render_options);
	}
	if (event->key.keysym.scancode == SDL_SCANCODE_P)
	{
		rt_set_render_algo(&rt->render_options, RENDER_PATHTRACE);
		rt_set_bit(&rt->render_actions, ACTION_PATHTRACE);
		sync_rt_and_gui(rt->scene, rt->render_options);
	}
	if (event->key.keysym.scancode == SDL_SCANCODE_M)
		rt_switch_bit(&rt->render_options, RENDER_MESH);
	if (event->key.keysym.scancode == SDL_SCANCODE_O)
		rt_switch_bit(&rt->render_options, RENDER_OBJECTS);
	if (event->key.keysym.scancode == SDL_SCANCODE_T)
		rt_switch_bit(&rt->render_options, RENDER_TEXTURES);
	if (event->key.keysym.scancode == SDL_SCANCODE_B)
		rt_switch_bit(&rt->render_options, RENDER_ANTI_ALIASING);
	if (event->key.keysym.scancode == SDL_SCANCODE_N)
		rt_switch_bit(&rt->render_options, RENDER_SMOOTH_NORMALS);
	if (event->key.keysym.scancode == SDL_SCANCODE_C)
		rt_switch_bit(&rt->render_options, RENDER_BACKFACE_CULLING);
	if (event->key.keysym.scancode == SDL_SCANCODE_Y)
		rt_switch_bit(&rt->render_options, RENDER_SKYBOX);
	if (event->key.keysym.scancode == SDL_SCANCODE_G)
		rt_switch_bit(&rt->render_state, STATE_POSTPROCESS_DOF);
	if (event->key.keysym.scancode == SDL_SCANCODE_H)
		rt_switch_bit(&rt->render_state, STATE_POSTPROCESS_SEPIA);
	if (event->key.keysym.scancode == SDL_SCANCODE_U)
		rt_switch_bit(&rt->render_options, RENDER_IMPRESSIVE);
	if (event->key.keysym.scancode == SDL_SCANCODE_K)
		rt_switch_bit(&rt->render_state, STATE_POSTPROCESS_CARTOON);
	keypress_change_dof(event, &rt->scene.camera);
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
