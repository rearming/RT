#include "rt.h"

void	render_kernel_reset_samples(t_list *list)
{
	((t_render_kernel*)list->content)->samples_num = 0;
}

void	rt_update_render_params(t_render_kernel *render_kernel,
							 t_render_params *params,
							 uint32_t render_options,
							 uint32_t render_state)
{
	if (rt_bit_isset(render_options, RENDER_PATHTRACE))
	{
		params->seed = drand48();
		params->pathtrace_params.current_samples_num = render_kernel->samples_num;
		render_kernel->samples_num++;
	}
	if (rt_bit_isset(render_state, STATE_CAMERA_CHANGED))
		ft_lstmap(g_opencl.kernels, &render_kernel_reset_samples);
}
