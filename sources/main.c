#include "rt.h"
#include "gui.h"

t_opencl	g_opencl;
t_sdl		g_sdl;
t_gui		g_gui;
int			*g_img_data;
cl_float3	g_img_data_float[WIN_WIDTH * WIN_HEIGHT];

int		main(int argc, char **argv)
{
	t_rt		rt;
	t_gui 		gui;

	RT_UNUSED(argv);
	if (argc != VALID_ARGS_NUM)
		rt_raise_error(ERR_INV_ARGS_NUM);
	rt_init(&rt, NULL);
	gui = init_gui_s();
	rt_render(&rt, &rt_opencl_render);
	rt_loop(&rt, gui);
	return (rt_exit_clean());
}

