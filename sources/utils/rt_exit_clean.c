#include "rt.h"

void		rt_del_renderer(void *renderer_ptr, size_t size)
{
	t_rt_renderer	*renderer;
	int				i;

	(void)size;
	renderer = ((t_list*)renderer_ptr)->content;
	i = 0;
	while (i < renderer->buffers_num)
	{
		if (renderer->buffers[i].copy_mem == false)
			clReleaseMemObject(renderer->buffers[i].mem);
		i++;
	}
	clReleaseKernel(renderer->kernel);
	clReleaseProgram(renderer->program);
	free(renderer->buffers);
}

bool		rt_exit_clean(void)
{
	int err;

	err = 0;
	ft_lstdel(&g_opencl.renderers, &rt_del_renderer);
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
