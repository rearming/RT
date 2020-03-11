#include "rt.h"
#include "rt_opencl.h"

void rt_opencl_create_kernel(const char *kernel_path,
							 const char *kernel_name,
							 const char *compile_options,
							 cl_kernel *out_kernel)
{
	static size_t	size = 0;
	char			*opencl_kernel_code;
	int				err;
	cl_program		program;

//	if (!opencl_kernel_code) //кешировать kernel код
	opencl_kernel_code = get_opencl_kernel_code_text(kernel_path, &size);
	program = clCreateProgramWithSource(g_opencl.context, 1,
			(const char **)&opencl_kernel_code, &size, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_PROGRAM, err);
	if ((err = clBuildProgram(
			program, 1, &g_opencl.device_id, compile_options, NULL, NULL)))
	{
		print_cl_build_program_debug(program);
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	*out_kernel = clCreateKernel(program, kernel_name, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_KERNEL, err);
	free(opencl_kernel_code);
	free((char*)compile_options); //todo remove
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void		rt_opencl_init(void)
{
	int			err;

	setenv("CUDA_CACHE_DISABLE", "1", 1);
	err = clGetPlatformIDs(
			2, g_opencl.platform_ids, &g_opencl.ret_num_platforms);
	rt_opencl_handle_error(ERR_OPENCL_GET_PLATFORM_ID, err);
	err = clGetDeviceIDs(
			g_opencl.platform_ids[0], CL_DEVICE_TYPE_GPU, 1,
			&g_opencl.device_id, &g_opencl.ret_num_devices);
	rt_opencl_handle_error(ERR_OPENCL_GET_DEVICE_ID, err);
	g_opencl.context = clCreateContext(
			NULL, 1, &g_opencl.device_id, NULL, NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_CONTEXT, err);
	g_opencl.queue = clCreateCommandQueue(
			g_opencl.context, g_opencl.device_id, CL_QUEUE_PROFILING_ENABLE , &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_QUEUE, err);
	g_opencl.renderers = NULL;
	g_opencl.wavefront_shared_buffers = NULL;
	g_opencl.shared_buffers_copy_done = false;
}

#pragma clang diagnostic pop

