/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_gui.h"
#include "rt_opencl.h"
#include "rt_window_params.h"

t_opencl	g_opencl;
t_sdl		g_sdl;
t_gui		g_gui;
int			*g_img_data;
t_textures	g_textures;
cl_float3	g_img_data_float[WIN_WIDTH * WIN_HEIGHT];

int		main(int argc, char **argv)
{
	t_rt		rt;

	if (argc < MIN_ARGS_NUM)
		rt_raise_error(ERR_INV_ARGS_NUM);
	rt_init(&rt, argv[1], rt_parse_init_options(argv, argc, 2));
	init_gui(rt.render_options, 0, rt.scene);
	rt_render(&rt, &rt_opencl_render);
	rt_loop(&rt);
	exit(rt_exit_clean());
	return (0);
}
