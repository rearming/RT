#include "rt.h"
#include "rt_opencl.h"

void		rt_opencl_alloc_buffers(uint32_t render_state, t_opencl_mem_obj *memobjs)
{
	int					i;
	int					err;

	i = 0;
	if (render_state & STATE_INIT)
		g_opencl.buffers = rt_safe_malloc(g_opencl.buffers_num * sizeof(t_cl_buffer));
	while (i < g_opencl.buffers_num)
	{
		if (memobjs[i].render_state & render_state)
		{
			g_opencl.buffers[i].mem = clCreateBuffer(g_opencl.context,
					memobjs[i].mem_flags, memobjs[i].size, memobjs[i].ptr, &err);
			g_opencl.buffers[i].render_state = memobjs[i].render_state;
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		g_opencl.buffers[i].render_state = memobjs[i].render_state;
		i++;
	}
}

void			rt_opencl_release_buffers(uint32_t current_render_state)
{
	for (int i = 0; i < g_opencl.buffers_num; ++i)
	{
		if (g_opencl.buffers[i].render_state & current_render_state || current_render_state & STATE_EXIT)
			clReleaseMemObject(g_opencl.buffers[i].mem);
	}
	if (current_render_state & STATE_EXIT)
		free(g_opencl.buffers);
}
