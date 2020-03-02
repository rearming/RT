#include "rt.h"
#include "rt_gui.h"
#include "rt_opencl.h"

t_opencl	g_opencl;
t_sdl		g_sdl;
t_gui		g_gui;
int			*g_img_data;
t_textures  g_textures;
cl_float3	g_img_data_float[WIN_WIDTH * WIN_HEIGHT];

int		main(int argc, char **argv)
{
	t_rt		rt;

	if (argc != VALID_ARGS_NUM)
		rt_raise_error(ERR_INV_ARGS_NUM);
	rt_init(&rt, argv[1]);
	init_gui(rt.renderer_flags);
//	rt_render(&rt, &rt_opencl_render);
	rt_render(&rt, wavefront);
	while (21);
//	rt_loop(&rt);
	exit(rt_exit_clean());
	return (0);
}
