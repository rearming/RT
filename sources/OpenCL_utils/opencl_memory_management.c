#include "rt.h"

void		rt_opencl_move_host_mem_to_kernel(int kernel_mem_object_nbr, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;
	static bool		mem_copy_done = false;

	va_start(ap, kernel_mem_object_nbr);
	mem_obj_i = 0;
	if (mem_copy_done == false) //маллочить память ТОЛЬКО ОДИН РАЗ БЛЯТБ
		g_opencl.opencl_mem = rt_safe_malloc(kernel_mem_object_nbr * sizeof(t_cl_buffer));
	while (mem_obj_i < kernel_mem_object_nbr)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (memobj.copy_mem == true || mem_copy_done == false)
		{
			g_opencl.opencl_mem[mem_obj_i].mem = clCreateBuffer(g_opencl.context,
					memobj.mem_flags, memobj.size, memobj.ptr, &err);
			g_opencl.opencl_mem[mem_obj_i].copy_mem = memobj.copy_mem;
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		err = clSetKernelArg(g_opencl.kernel, mem_obj_i, sizeof(cl_mem),
							 &g_opencl.opencl_mem[mem_obj_i].mem);
		rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
		mem_obj_i++;
	}
	mem_copy_done = true;
	va_end(ap);
}

void		opencl_clean_memobjs(void)
{
	int		memobj_i;

	memobj_i = 0;
	while (memobj_i < g_opencl.opencl_memobj_number)
	{
//		printf("copy_mem == %s", g_opencl.opencl_mem[memobj_i].copy_mem == true ? "true, " : "false\n");
		if (g_opencl.opencl_mem[memobj_i].copy_mem == true)
		{
//			printf("Releasing memobj\n");
			if (clReleaseMemObject(g_opencl.opencl_mem[memobj_i].mem))
				ft_printf_fd(STDERR_FILENO, "clReleaseMemObject on %i object failed!\n", memobj_i);
		}
		memobj_i++;
	}
}
