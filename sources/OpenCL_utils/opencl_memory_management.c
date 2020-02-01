#include "rt.h"

void		rt_opencl_move_host_mem_to_kernel(cl_kernel kernel, uint32_t renderer_flags, int kernel_mem_object_nbr, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;
	static bool			mem_copy_done = false;
	int					real_passed_memobj_nbr = 0; //todo рефактор

	va_start(ap, kernel_mem_object_nbr);
	mem_obj_i = 0;
	if (mem_copy_done == false) //маллочить память ТОЛЬКО ОДИН РАЗ БЛЯТБ
		g_opencl.opencl_mem = rt_safe_malloc(kernel_mem_object_nbr * sizeof(t_cl_buffer));
	while (mem_obj_i < kernel_mem_object_nbr)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (!(renderer_flags & memobj.renderer_flags))
		{
			mem_obj_i++;
			continue;
		}
		if (memobj.copy == true || mem_copy_done == false)
		{
			g_opencl.opencl_mem[mem_obj_i].mem = clCreateBuffer(g_opencl.context,
					memobj.mem_flags, memobj.size, memobj.ptr, &err);
			g_opencl.opencl_mem[mem_obj_i].copy_mem = memobj.copy;
			g_opencl.opencl_mem[mem_obj_i].renderer_flags = memobj.renderer_flags;
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err); //todo удалить две структуры, просто сделать в том поле cl_mem
		}
		err = clSetKernelArg(kernel, mem_obj_i, sizeof(cl_mem),
							 &g_opencl.opencl_mem[mem_obj_i].mem);
		rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
		mem_obj_i++;
		real_passed_memobj_nbr++;
	}
	g_opencl.opencl_memobj_number = real_passed_memobj_nbr;
	// чтобы потом сделать setarg image на правильное место (может это тоже делать через эту функцию?)
	mem_copy_done = true;
	va_end(ap);
}

void	opencl_clean_memobjs(uint32_t renderer_flags)
{
	int		memobj_i;

	memobj_i = 0;
	while (memobj_i < g_opencl.opencl_memobj_number)
	{
//		printf("copy == %s", g_opencl.opencl_mem[memobj_i].copy == true ? "true, " : "false\n");
		if (g_opencl.opencl_mem[memobj_i].copy_mem == true
		&& renderer_flags & g_opencl.opencl_mem[memobj_i].renderer_flags)
		{
//			printf("Releasing memobj\n");
			if (clReleaseMemObject(g_opencl.opencl_mem[memobj_i].mem))
				ft_printf_fd(STDERR_FILENO, "clReleaseMemObject on %i object failed!\n", memobj_i);
		}
		memobj_i++;
	}
}
