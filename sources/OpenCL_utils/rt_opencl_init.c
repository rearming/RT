#include "rt.h"
#include "rt_opencl.h"

void		rt_opencl_create_kernel(const char *compile_options,
							 cl_kernel *out_kernel,
							 cl_program *out_program)
{
	static size_t	size = 0;
	static char		*opencl_kernel_code = NULL;
	int				err;

	if (!opencl_kernel_code) //кешировать kernel код
		opencl_kernel_code = get_opencl_kernel_code_text(&size);
	*out_program = clCreateProgramWithSource(g_opencl.context, 1,
			(const char **)&opencl_kernel_code, &size, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_PROGRAM, err); //todo ft_del_whitespaces(compile_options);
	if ((err = clBuildProgram(
			*out_program, 1, &g_opencl.device_id, compile_options, NULL, NULL)))
	{
		print_cl_build_program_debug(*out_program);
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	*out_kernel = clCreateKernel(*out_program, OPENCL_KERNEL_NAME, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_KERNEL, err);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void		rt_opencl_init(void)
{
	int			err;

	setenv("CUDA_CACHE_DISABLE", "1", 1);
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
	g_opencl.renderers = NULL;
}

#pragma clang diagnostic pop

