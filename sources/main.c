#include "rt.h"

t_opencl	g_opencl;
t_sdl		g_sdl;
int			*g_img_data;
cl_float3	g_img_data_float[WIN_WIDTH * WIN_HEIGHT];

int		main(int argc, char **argv)
{
	t_rt		rt;

	if (argc != VALID_ARGS_NUM)
		rt_raise_error(ERR_INV_ARGS_NUM);
	rt_init(&rt, argv[1]);
	//rt_render(&rt, &rt_opencl_render);
	//rt_loop(&rt);
	return (rt_exit_clean());
}
