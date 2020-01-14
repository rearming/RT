#include "rt.h"

void		rt_opencl_compile_kernel(void)
{
	int			err;
	char		*opencl_kernel_file;
	size_t		size;

	opencl_kernel_file = get_opencl_kernel_code_text(&size);
	g_opencl.program = clCreateProgramWithSource(g_opencl.context, 1,
			(const char **)&opencl_kernel_file, &size, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_PROGRAM, err);
	if ((err = clBuildProgram(
			g_opencl.program, 1, &g_opencl.device_id, NULL, NULL, NULL)))
	{
		print_cl_build_program_debug();
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	g_opencl.kernel = clCreateKernel(g_opencl.program, OPENCL_KERNEL_NAME, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_KERNEL, err);
	free(opencl_kernel_file);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void		rt_opencl_init(void)
{
	int			err;

	err = clGetPlatformIDs(
			1, &g_opencl.platform_id, &g_opencl.ret_num_platforms);
	rt_opencl_handle_error(ERR_OPENCL_GET_PLATFORM_ID, err);
	err = clGetDeviceIDs(
			g_opencl.platform_id, CL_DEVICE_TYPE_GPU, 1,
			&g_opencl.device_id, &g_opencl.ret_num_devices);
	rt_opencl_handle_error(ERR_OPENCL_GET_DEVICE_ID, err);
	g_opencl.context = clCreateContext(
			NULL, 1, &g_opencl.device_id, NULL, NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_CONTEXT, err);
	g_opencl.queue = clCreateCommandQueue(
			g_opencl.context, g_opencl.device_id, CL_QUEUE_PROFILING_ENABLE , &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_QUEUE, err);
	rt_opencl_compile_kernel();
}

#pragma clang diagnostic pop

