#include "rt.h"

void		rt_opencl_compile_kernel(void)
{
	int			err;
	char		*opencl_kernel_file;
	size_t		size;

	opencl_kernel_file = get_opencl_kernel_code_text(&size);
	g_opencl.program = clCreateProgramWithSource(g_opencl.context, 1,
			(const char **)&opencl_kernel_file, &size, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_PROGRAM);
	if ((err = clBuildProgram(
			g_opencl.program, 1, &g_opencl.device_id, NULL, NULL, NULL)))
	{
		print_cl_build_program_debug();
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	g_opencl.kernel = clCreateKernel(
			g_opencl.program, OPENCL_KERNEL_NAME, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_KERNEL);
	free(opencl_kernel_file);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void		rt_opencl_init(void)
{
	int			err;

	err = clGetPlatformIDs(
			1, &g_opencl.platform_id, &g_opencl.ret_num_platforms);
	if (err)
		rt_raise_error(ERR_OPENCL_GET_PLATFORM_ID);
	err = clGetDeviceIDs(
			g_opencl.platform_id, CL_DEVICE_TYPE_GPU, 1,
			&g_opencl.device_id, &g_opencl.ret_num_devices);
	if (err)
		rt_raise_error(ERR_OPENCL_GET_DEVICE_ID);
	g_opencl.context = clCreateContext(
			NULL, 1, &g_opencl.device_id, NULL, NULL, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_CONTEXT);
	g_opencl.queue = clCreateCommandQueue(
			g_opencl.context, g_opencl.device_id, CL_QUEUE_PROFILING_ENABLE , &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_QUEUE);
	rt_opencl_compile_kernel();
}

#pragma clang diagnostic pop

