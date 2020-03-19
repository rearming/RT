#include "rt.h"
#include "rt_opencl.h"

void		rt_read_img_buffer(void)
{
	int			err;

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.buffers[switch_img_buffers(NULL, NULL)].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT, g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void		rt_opencl_render(void *rt_ptr)
{
	const size_t		global_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};
	t_rt				*rt;

	rt = rt_ptr;
	if (!rt_bit_isset(rt->render_actions, ACTION_INIT))
		rt_opencl_release_buffers(rt->render_actions);
	else
		rt_opencl_compile_kernels(rt->render_options);
	rt_opencl_prepare_memory(rt, rt->render_actions);
	exec_render_kernel(rt, rt_get_render_kernel(rt->render_options),
			global_work_size);
	exec_depth_of_field_kernel(rt, g_opencl.kernels[KERNEL_GAUSS_BLUR],
			global_work_size);
	exec_sepia_kernel(rt, g_opencl.kernels[KERNEL_SEPIA], global_work_size);
	rt_read_img_buffer();
	rt->render_actions &= ACTION_PATHTRACE;
}
