#ifndef RT_EVENTS_H
# define RT_EVENTS_H

#define MAX_EVENT_IN_LIST 30

typedef enum	s_events
{
	EVENT_NOTHING = 0x0,
	EVENT_W = (1 << 0),
	EVENT_A = (1 << 1),
	EVENT_S = (1 << 2),
	EVENT_D = (1 << 3),
	EVENT_INFO = (1 << 4),
	EVENT_SPACE = (1 << 5),
	EVENT_LSHIFT = (1 << 6),
}				t_events;

bool		rt_handle_mouse_event(SDL_Event *event, t_rt *rt);
bool		rt_handle_key_event(SDL_Event *event, t_rt *rt);
bool		rt_camera_move(t_camera *camera, uint32_t events);

#endif
