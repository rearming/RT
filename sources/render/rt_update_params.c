#include "rt.h"

void rt_update_render_params(t_render_kernel *render_kernel,
							 t_render_params *params,
							 uint32_t render_options,
							 uint32_t render_state)
{
	t_list	*temp_render_kernel;

	if (rt_bit_isset(render_options, RENDER_PATHTRACE))
	{
		params->seed = drand48();
		params->pathtrace_params.current_samples_num = render_kernel->samples_num;
		render_kernel->samples_num++;
	}
	if (rt_bit_isset(render_state, STATE_CAMERA_CHANGED))
	{
		//todo add libft listmap function [sleonard]
		temp_render_kernel = g_opencl.kernels;
		while (temp_render_kernel)
		{
			((t_render_kernel*)temp_render_kernel->content)->samples_num = 0;
			temp_render_kernel = temp_render_kernel->next;
		}
	}
}
