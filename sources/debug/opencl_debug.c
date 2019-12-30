#include "rt.h"

void		print_cl_build_program_debug(void)
{
	size_t		log_size;
	char		*log;

	clGetProgramBuildInfo(g_opencl.program, g_opencl.device_id,
			CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = rt_safe_malloc(log_size);
	clGetProgramBuildInfo(g_opencl.program, g_opencl.device_id,
			CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	ft_printf("OpenCL Log:\n%s\n", log);
	free(log);
}
