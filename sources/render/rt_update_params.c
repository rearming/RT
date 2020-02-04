#include "rt.h"

void		rt_update_renderer_params(t_rt *rt, t_rt_renderer *renderer)
{
	if (rt_params_isset(renderer->flags, RENDER_PATHTRACE))
	{
		renderer->params.seed = drand48();
		renderer->params.pathtrace_params.current_samples_num++;
	}
	if (rt_camera_moved(&rt->scene.camera))
	{
		//todo add libft listmap function [sleonard]
		t_list	*temp = g_opencl.renderers;
		while (temp)
		{
			((t_rt_renderer*)temp->content)->params.pathtrace_params.current_samples_num = 0;
			temp = temp->next;
		}
	}
}
