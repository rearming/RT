#include "rt.h"
#include "rt_debug_utils.h"

void		rt_print_debug_info(t_rt *rt)
{
	ft_putchar('\n');
	ft_printf("\033[0;33m");
	ft_printf("camera position: ");
	print_clfloat3(rt->scene.camera.pos);
	ft_printf("camera rotation: ");
	print_clfloat3(rt->scene.camera.rotation);
	ft_printf("\033[0m");
}
