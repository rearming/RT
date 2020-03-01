#include "rt.h"
#include "rt_gui.h"

bool		rt_handle_mouse_event(SDL_Event *event, t_rt *rt)
{
	bool	event_handled;

	event_handled = false;
	if (event->type == SDL_MOUSEMOTION && SDL_GetRelativeMouseMode())
	{
		rt->scene.camera.rotation.x -=
				event->motion.yrel * ROTATION_SPEED * WIN_RATIO;
		rt->scene.camera.rotation.y += event->motion.xrel * ROTATION_SPEED;
		event_handled = true;
	}
	return (event_handled);
}
