#include "rt.h"
#include "rt_opencl.h"

void		rt_opencl_alloc_buffers(uint32_t render_state, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;

	va_start(ap, render_state);
	mem_obj_i = 0;
	while (mem_obj_i < g_opencl.buffers_num)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (memobj.render_state & render_state)
		{
			g_opencl.buffers[mem_obj_i].mem = clCreateBuffer(g_opencl.context,
					memobj.mem_flags, memobj.size, memobj.ptr, &err);
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		g_opencl.buffers[mem_obj_i].render_state = memobj.render_state;
		mem_obj_i++;
	}
	va_end(ap);
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
