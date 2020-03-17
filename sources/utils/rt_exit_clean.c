#include "rt.h"
#include "rt_opencl.h"

void		rt_release_render_kernel(void *renderer_ptr, size_t size)
{
	t_render_kernel *render_kernel;
	int				err;

	(void)size;
	render_kernel = ((t_list*)renderer_ptr)->content;
	err = clReleaseMemObject(render_kernel->img_data_float);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_BUFFER, err);
	err = clReleaseKernel(render_kernel->kernel);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_KERNEL, err);
}

bool		rt_exit_clean(void)
{
	int err;

	err = 0;
	rt_opencl_release_buffers(ACTION_EXIT);
	ft_lstdel(&g_opencl.kernels, &rt_release_render_kernel);
	if (g_opencl.queue)
	{
		err |= clFlush(g_opencl.queue);
		err |= clFinish(g_opencl.queue);
		err |= clReleaseCommandQueue(g_opencl.queue);
	}
	if (g_opencl.device_id)
		err |= clReleaseDevice(g_opencl.device_id);
	if (g_opencl.context)
		err |= clReleaseContext(g_opencl.context);
	if (err)
		rt_raise_error(ERR_OPENCL_CLEAN);
	SDL_DestroyRenderer(g_sdl.rend);
	SDL_DestroyWindow(g_sdl.win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
