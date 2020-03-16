#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_events.h"

void		rt_opencl_prepare_kernel(t_render_kernel *render_kernel)
{
	int		i;
	int		err;

	i = 0;
	while (i < g_opencl.buffers_num)
	{
		err = clSetKernelArg(render_kernel->kernel, i, sizeof(cl_mem), &g_opencl.buffers[i].mem);
		rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
		i++;
	}
	err = clSetKernelArg(render_kernel->kernel, i, sizeof(cl_mem), &render_kernel->img_data_float);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
}

void		rt_opencl_render(void *rt_ptr)
{
	const size_t		global_work_size[2] = {WIN_WIDTH, WIN_HEIGHT};
	int					err;
	t_render_kernel		*render_kernel;
	t_rt				*rt;

	rt = rt_ptr;
	if (!rt_bit_isset(rt->render_state, STATE_INIT))
		rt_opencl_release_buffers(rt->render_state);
	render_kernel = rt_get_render_kernel(rt->render_options);
	rt_update_render_params(render_kernel, &rt->params, rt->render_options, rt->render_state);
	rt_opencl_prepare_memory(rt, rt->render_state);
	rt_opencl_prepare_kernel(render_kernel);
	if (rt_bit_isset(rt->events, EVENT_INFO))
		rt_print_debug_info(rt, render_kernel);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			render_kernel->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt_bit_isset(rt->events, EVENT_INFO))
		rt_print_opencl_profile_info();
	err = clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_EVENT, err);
	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.buffers[RT_CL_MEM_IMG_DATA].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT, g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	rt->render_state = rt->render_options & RENDER_PATHTRACE ? STATE_PATHTRACE : STATE_NOTHING;
}
