#include "rt.h"
#include "rt_gui.h"
#include "rt_events.h"
#include "rt_opencl.h"
#include "rt_debug.h"

void handle_event(t_rt *rt, SDL_Event *events, int events_num)
{
	bool	key_event_handled = false;
	bool	mouse_event_handled = false;
	bool	gui_event_handled = false;

	for (int i = 0; i < events_num; ++i)
	{
		key_event_handled = rt_handle_key_event(&events[i], rt);
		mouse_event_handled = rt_handle_mouse_event(&events[i], rt);
		gui_event_handled = rt_handle_event_gui(&events[i], rt);
	}
	if (key_event_handled || mouse_event_handled || gui_event_handled || rt->events)
	{
		rt_camera_move(&rt->scene.camera, rt->events);
		if (rt_camera_moved(&rt->scene.camera))
			rt->render_state |= STATE_CAMERA_CHANGED;
		rt_render(rt, &rt_opencl_render);
	}
}
