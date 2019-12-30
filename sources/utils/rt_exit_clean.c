#include "rt.h"

t_bool		rt_exit_clean(void)
{
	int		err;

	err = 0;
	if (g_opencl.queue)
	{
		err += clFlush(g_opencl.queue);
		err += clFinish(g_opencl.queue);
		err += clReleaseCommandQueue(g_opencl.queue);
	}
	if (g_opencl.device_id)
		err += clReleaseDevice(g_opencl.device_id);
	if (g_opencl.kernel)
		err += clReleaseKernel(g_opencl.kernel);
	if (g_opencl.program)
		err += clReleaseProgram(g_opencl.program);
	if (g_opencl.context)
		err += clReleaseContext(g_opencl.context);
	if (err)
		rt_raise_error(ERR_OPENCL_CLEAN);
	SDL_DestroyRenderer(g_sdl.rend);
	SDL_DestroyWindow(g_sdl.win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
