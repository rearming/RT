#ifndef RT_EVENTS_H
# define RT_EVENTS_H

bool		rt_handle_mouse_event(SDL_Event *event, t_rt *rt);
bool		rt_handle_key_event(SDL_Event *event, t_rt *rt);
bool rt_camera_move(t_camera *camera, uint32_t events);

#endif
