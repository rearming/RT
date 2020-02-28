#ifndef RT_EVENTS_H
# define RT_EVENTS_H

bool		rt_handle_mouse_event(SDL_Event *event, t_rt *rt);
bool		rt_handle_key_event(SDL_Event *event, t_rt *rt);
void		rt_camera_move(t_camera *camera, t_events *events);

#endif
