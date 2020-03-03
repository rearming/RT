#include "rt.h"
#include "rt_opencl.h"

void		rt_opencl_move_host_mem_to_kernel(t_rt_renderer *renderer, int max_memobj_num, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;

	va_start(ap, max_memobj_num);
	mem_obj_i = 0;
	if (renderer->copy_done == false) //маллочить память ТОЛЬКО ОДИН РАЗ БЛЯТБ
		renderer->buffers = rt_safe_malloc(max_memobj_num * sizeof(t_cl_buffer));
	renderer->buffers_num = 0;
	while (mem_obj_i < max_memobj_num)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (!(renderer->flags & memobj.renderer_flags))
		{
			mem_obj_i++;
			continue;
		}
		if (memobj.copy == true || renderer->copy_done == false)
		{
			renderer->buffers[renderer->buffers_num].mem = clCreateBuffer(g_opencl.context,
					memobj.mem_flags, memobj.size, memobj.ptr, &err);
			renderer->buffers[renderer->buffers_num].copy_mem = memobj.copy;
			renderer->buffers[renderer->buffers_num].renderer_flags = memobj.renderer_flags;
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		err = clSetKernelArg(renderer->main_kernel, renderer->buffers_num, sizeof(cl_mem),
							 &renderer->buffers[renderer->buffers_num].mem);
		rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
		mem_obj_i++;
		renderer->buffers_num++;
	}
	renderer->copy_done = true;
	va_end(ap);
}

void	opencl_clean_memobjs(t_rt_renderer *renderer)
{
	int		memobj_i;

	memobj_i = 0;
	while (memobj_i < renderer->buffers_num)
	{
//		printf("copy == %s", g_opencl.opencl_mem[memobj_i].copy == true ? "true, " : "false\n");
		if (renderer->buffers[memobj_i].copy_mem == true)
		{
//			printf("Releasing memobj\n");
			if (clReleaseMemObject(renderer->buffers[memobj_i].mem))
				ft_printf_fd(STDERR_FILENO, "clReleaseMemObject on %i object failed!\n", memobj_i);
		}
		memobj_i++;
	}
}
