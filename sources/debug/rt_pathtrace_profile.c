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
	sleep(10);
}

