#include "rt.h"
#include "rt_debug.h"

void		rt_print_debug_info(t_rt *rt, t_rt_renderer *renderer)
{
	ft_putchar('\n');
	ft_printf("\033[0;33m");
	ft_printf("render with [%s] algo\n", rt->render_settings & RENDER_RAYTRACE ? "RAY_TRACE" : "PATH_TRACE");
	if (rt_params_isset(rt->render_settings, RENDER_PATHTRACE))
	{
		ft_printf("current samples number: [%i]\n", renderer->params.pathtrace_params.current_samples_num);
//		ft_printf("current seed: [%.4f]\n", rt->opencl_params.seed);
	}

	rt_print_clfloat3(rt->scene.camera.pos, "camera position");
	rt_print_clfloat3(rt->scene.camera.rotation, "camera rotation");
	ft_printf("\033[0m");
}
