#include "rt.h"
#include "rt_debug_utils.h"

void		rt_print_debug_info(t_rt *rt)
{
	ft_putchar('\n');
	ft_printf("\033[0;33m");
	ft_printf("render with [%s] algo\n", rt->opencl_params.render_algo == RAY_TRACE ? "RAY_TRACE" : "PATH_TRACE");
	if (rt->opencl_params.render_algo == PATH_TRACE)
	{
		ft_printf("current samples number: [%i]\n", rt->opencl_params.pathtrace_params.current_samples_num);
		ft_printf("current seed: [%.4f]\n", rt->opencl_params.seed);
	}

	ft_printf("camera position: ");
	rt_print_clfloat3(rt->scene.camera.pos);
	ft_printf("camera rotation: ");
	rt_print_clfloat3(rt->scene.camera.rotation);
	ft_printf("\033[0m");
}
