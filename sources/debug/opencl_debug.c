#include "rt.h"

void print_cl_build_program_debug(cl_program program)
{
	size_t		log_size;
	char		*log;

	clGetProgramBuildInfo(program, g_opencl.device_id,
			CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = rt_safe_malloc(log_size);
	clGetProgramBuildInfo(program, g_opencl.device_id,
			CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	ft_printf("OpenCL Log:\n%s\n", log);
	free(log);
}

void		print_cl_device_info(void)
{
	void		*param_value;
	size_t		info_size;

	clGetDeviceInfo(g_opencl.device_id, CL_DEVICE_NAME, 0, NULL, &info_size);
	param_value = rt_safe_malloc(info_size);
	clGetDeviceInfo(g_opencl.device_id, CL_DEVICE_NAME, info_size, param_value, NULL);
	ft_printf("device name: [%s]\n", (char*)param_value);
}