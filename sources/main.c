#include "rt.h"

t_opencl	g_opencl;
t_sdl		g_sdl;
int			*g_img_data;

int		main(int argc, char **argv)
{
	t_rt		rt;

	RT_UNUSED(argv);
	if (argc != VALID_ARGS_NUM)
		rt_raise_error(ERR_INV_ARGS_NUM);
	rt_init(&rt, NULL);
	//rt_render(&rt, &rt_opencl_render);
	//rt_loop(&rt);
	return (rt_exit_clean());
}
