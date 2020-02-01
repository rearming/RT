#include "rt.h"
#include <time.h>

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
	ft_printf("[%i] samples rendered in [%.3f] sec.\n",
			max_samples, (double)(end - start) / CLOCKS_PER_SEC);
}

void		rt_print_opencl_profile_info(void)
{
	clWaitForEvents(1, &g_opencl.profile_event);
	cl_ulong start = 0, end = 0;
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	cl_double nd_range_pure_exec_time_ms = (cl_double)(end - start) * (cl_double)(1e-06);
	ft_printf("\033[0;91m");
	ft_printf("kernel exec time: [%.2f]\n", nd_range_pure_exec_time_ms);
	ft_printf("\033[0m");
}
