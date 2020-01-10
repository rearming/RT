#include "rt.h"

inline void		rt_opencl_setup_image_buffer(void)
{
	int		err;

	g_opencl.img_data_mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE,
			sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_BUFFER);
	err = clSetKernelArg(g_opencl.kernel, g_opencl.opencl_memobj_number,
						 sizeof(cl_mem), &g_opencl.img_data_mem);
	if (err)
		rt_raise_error(ERR_OPENCL_SETARG);
}
