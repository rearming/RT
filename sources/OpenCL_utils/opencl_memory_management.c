#include "rt.h"

void		rt_opencl_move_host_mem_to_kernel(int kernel_mem_object_nbr, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;
	static t_bool		mem_copy_done = FALSE;

	va_start(ap, kernel_mem_object_nbr);
	mem_obj_i = 0;
	if (mem_copy_done == FALSE) //маллочить память ТОЛЬКО ОДИН РАЗ БЛЯТБ
		g_opencl.opencl_mem = rt_safe_malloc(kernel_mem_object_nbr * sizeof(t_cl_mem));
	while (mem_obj_i < kernel_mem_object_nbr)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		if (memobj.copy_mem == TRUE || mem_copy_done == FALSE)
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
	mem_copy_done = TRUE;
	va_end(ap);
}

void		cl_set_kernel(t_rt *rt, int mode)
{
	int		err;

	err = 0;
	if (mode == CREATE_BUFFER)
	{
		g_opencl.opencl_memobj_number = 4;
		g_opencl.opencl_mem = rt_safe_malloc(sizeof(cl_mem) * g_opencl.opencl_memobj_number);
		g_opencl.opencl_mem[0].mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
				sizeof(t_scene), &rt->scene, &err);
		g_opencl.opencl_mem[1].mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
				sizeof(t_object) * rt->scene.obj_nbr, rt->scene.objects, &err);
		g_opencl.opencl_mem[2].mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
				sizeof(t_light) * rt->scene.lights_nbr, rt->scene.lights, &err);
		g_opencl.opencl_mem[3].mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
				sizeof(t_light) * rt->scene.lights_nbr, rt->scene.lights, &err);
		g_opencl.img_data_mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE,
				sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
		rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	}
	err |= clSetKernelArg(g_opencl.kernel, 0, sizeof(cl_mem), &g_opencl.opencl_mem[0]);
	err |= clSetKernelArg(g_opencl.kernel, 1, sizeof(cl_mem), &g_opencl.opencl_mem[1]);
	err |= clSetKernelArg(g_opencl.kernel, 2, sizeof(cl_mem), &g_opencl.opencl_mem[2]);
	err |= clSetKernelArg(g_opencl.kernel, 3, sizeof(cl_mem), &g_opencl.opencl_mem[3]);
	err |= clSetKernelArg(g_opencl.kernel, 4, sizeof(cl_mem), &g_opencl.img_data_mem);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
}

void		opencl_clean_memobjs(void)
{
	int		memobj_i;

	memobj_i = 0;
	while (memobj_i < g_opencl.opencl_memobj_number)
	{
//		printf("copy_mem == %s", g_opencl.opencl_mem[memobj_i].copy_mem == TRUE ? "TRUE, " : "FALSE\n");
		if (g_opencl.opencl_mem[memobj_i].copy_mem == TRUE)
		{
//			printf("Releasing memobj\n");
			if (clReleaseMemObject(g_opencl.opencl_mem[memobj_i].mem))
				ft_printf_fd(STDERR_FILENO, "clReleaseMemObject on %i object failed!\n", memobj_i);
		}
		memobj_i++;
	}
	if (clReleaseMemObject(g_opencl.img_data_mem) != CL_SUCCESS)
		ft_printf_fd(STDERR_FILENO, "clReleaseMemObject on img_data_mem failed!\n");
	g_opencl.img_data_mem = NULL;
}
