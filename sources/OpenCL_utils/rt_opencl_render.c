#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"

void		rt_opencl_render(void *rt_ptr)
{
	const size_t	kernel_num = OPENCL_RELEASE_KERNEL_NUM;
	int				err;
	t_rt_renderer	*renderer;
	t_rt			*rt;

	rt = rt_ptr;
	renderer = rt_get_renderer(rt->renderer_flags);
	rt_opencl_prepare_memory(rt, renderer);
	rt_opencl_setup_image_buffer(renderer);
	rt_update_renderer_params(rt, renderer);
	if (rt->events.info)
		rt_print_debug_info(rt, renderer);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 1, NULL, &kernel_num, NULL, 0, NULL, &g_opencl.profile_event);
	if (rt->events.info)
		rt_print_opencl_profile_info();
	clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err |= clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	opencl_clean_memobjs(renderer);
}
