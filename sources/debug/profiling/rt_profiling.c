#include "rt.h"
#include <time.h>
#include "rt_opencl.h"

void	rt_pathtrace_profile(t_rt *rt, int max_samples)
{
	int		i;
	time_t	start;
	time_t	end;

	i = 0;
	start = clock();
	while (i < max_samples)
	{
		rt_render(rt, &rt_opencl_render);
		i++;
	}
	end = clock();
	printf("[%i] samples rendered in [%.3f] sec.\n",
			max_samples, (double)(end - start) / CLOCKS_PER_SEC);
}

float rt_get_kernel_exec_time(void)
{
	clWaitForEvents(1, &g_opencl.profile_event);
	cl_ulong start = 0, end = 0;
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	return (float)((cl_double)(end - start) * (cl_double)(1e-06));
}

void rt_print_opencl_profile_info(const char *kernel_name)
{
	printf("\033[0;91m");
	printf("[%s] exec time: [%.2f]\n", kernel_name, rt_get_kernel_exec_time());
	printf("\033[0m");
}
