#include "rt.h"

void rt_update_render_params(t_render_params *params,
							 uint32_t render_options,
							 uint32_t render_state)
{
	if (rt_bit_isset(render_options, RENDER_PATHTRACE))
	{
		params->seed = drand48();
		params->pathtrace_params.current_samples_num++;
	}
	if (rt_bit_isset(render_state, STATE_CAMERA_CHANGED))
	{
		//todo add libft listmap function [sleonard]
		t_list	*temp = g_opencl.kernels;
		while (temp)
		{
			((t_render_kernel*)temp->content)->samples_num = 0;
			temp = temp->next;
		}
	}
}
