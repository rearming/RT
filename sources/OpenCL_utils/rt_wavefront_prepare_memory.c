#include "rt.h"
#include "rt_opencl.h"

void		rt_wavefront_render_prepare_shared_memory(t_rt *rt, int memobj_num, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;

	va_start(ap, memobj_num);
	mem_obj_i = 0;
	if (g_opencl.shared_buffers_copy_done == false) //маллочить память ТОЛЬКО ОДИН РАЗ БЛЯТБ
		g_opencl.wavefront_shared_buffers = rt_safe_malloc(memobj_num * sizeof(t_cl_buffer));
	while (mem_obj_i < memobj_num)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (memobj.copy == true || g_opencl.shared_buffers_copy_done == false)
		{
			g_opencl.wavefront_shared_buffers[mem_obj_i].mem = clCreateBuffer(g_opencl.context,
					memobj.mem_flags, memobj.size, memobj.ptr, &err);
			g_opencl.wavefront_shared_buffers[mem_obj_i].copy_mem = memobj.copy;
			g_opencl.wavefront_shared_buffers[mem_obj_i].renderer_flags = memobj.renderer_flags;
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		mem_obj_i++;
	}
	g_opencl.shared_buffers_copy_done = true;
	va_end(ap);
}
