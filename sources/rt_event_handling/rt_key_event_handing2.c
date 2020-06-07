#include "rt.h"
#include "rt_events.h"
#include "rt_gui.h"

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

void					rt_handle_keypress2(SDL_Event *event, t_rt *rt)
{
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
