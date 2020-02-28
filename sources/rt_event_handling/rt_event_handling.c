#include "rt.h"
#include "rt_gui.h"
#include "rt_events.h"
#include "rt_opencl.h"

void		handle_event(SDL_Event *event, t_rt *rt)
{
	const bool	key_event_handled = rt_handle_key_event(event, rt);
	const bool	mouse_event_handled = rt_handle_mouse_event(event, rt);
	const bool	tools_event_handled = rt_handle_event_gui(event, rt);

	if (key_event_handled || mouse_event_handled || tools_event_handled)
	{
		rt_camera_move(&rt->scene.camera, &rt->events);
		rt_render(rt, &rt_opencl_render);
	}
	else if (event->type != SDL_MOUSEMOTION)
	{

	}
}
