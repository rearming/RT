#include "rt.h"

void		rt_init(t_rt *out_rt, const char *json_scene_file)
{
	rt_sdl_init();
	rt_opencl_init();
	out_rt->scene = rt_parse_scene(json_scene_file);
}
