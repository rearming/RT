#include "rt.h"

void		rt_opencl_copy_host_mem_to_kernel(int kernel_mem_object_nbr, ...)
{
	va_list				ap;
	t_opencl_mem_obj	memobj;
	int					mem_obj_i;
	int					err;

	va_start(ap, kernel_mem_object_nbr);
	mem_obj_i = 0;
	g_opencl.opencl_mem = rt_safe_malloc(kernel_mem_object_nbr * sizeof(cl_mem));
	while (mem_obj_i < kernel_mem_object_nbr)
	{
		memobj = va_arg(ap, t_opencl_mem_obj);
		g_opencl.opencl_mem[mem_obj_i] = clCreateBuffer(g_opencl.context,
				memobj.mem_flags, memobj.size, memobj.ptr, &err);
		if (err)
			rt_raise_error(ERR_OPENCL_CREATE_BUFFER);
		err = clSetKernelArg(g_opencl.kernel, mem_obj_i, sizeof(cl_mem),
				&g_opencl.opencl_mem[mem_obj_i]);
		if (err)
			rt_raise_error(ERR_OPENCL_SETARG);
		mem_obj_i++;
	}
	va_end(ap);
}

void		cl_set_kernel(t_rt *rtv1, t_opencl *cl)
{
//	int		err;
//
//	err = 0;
//	cl->scene = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//			sizeof(t_scene), &rtv1->scene, &err);
//	cl->objects = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//			sizeof(t_object) * rtv1->scene.obj_nbr, rtv1->scene.objects, &err);
//	cl->lights = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//			sizeof(t_light) * rtv1->scene.lights_nbr, rtv1->scene.lights, &err);
//	cl->camera = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//			sizeof(t_camera), &rtv1->camera, &err);
//	cl->img_data_mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
//			sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
//	if (err)
//		raise_error(ERR_OPENCL_CREATE_BUFFER);
//	err += clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->scene);
//	err += clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->objects);
//	err += clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->lights);
//	err += clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->camera);
//	err += clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->img_data_mem);
//	if (err)
//		raise_error(ERR_OPENCL_SETARG);
}

void		opencl_clean_memobjs(void)
{
	int		memobj_i;

	memobj_i = 0;
	while (memobj_i < g_opencl.opencl_memobj_number)
	{
		if (clReleaseMemObject(g_opencl.opencl_mem[memobj_i]) != CL_SUCCESS)
			ft_printf_fd(STDERR_FILENO, "clReleaseMemObject failed!\n");
		memobj_i++;
	}
	if (clReleaseMemObject(g_opencl.img_data_mem) != CL_SUCCESS)
		ft_printf_fd(STDERR_FILENO, "clReleaseMemObject failed!\n");
	g_opencl.img_data_mem = NULL;
}
