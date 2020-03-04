#include "rt.h"
#include "rt_gui.h"

void		change_render_algo(short algo, t_rt *rt)
{
	rt_set_render_algo(&rt->renderer_flags, 1 << (algo));
}
