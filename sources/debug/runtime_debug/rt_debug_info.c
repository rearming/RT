/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_debug_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_debug.h"

void		rt_print_debug_info(t_rt *rt, t_render_kernel *kernel)
{
	ft_printf("\n");
	ft_printf("\033[0;33m");
	ft_printf("render with [%s] algo\n",
			rt->render_options & RENDER_RAYTRACE ? "RAY_TRACE" : "PATH_TRACE");
	if (rt_bit_isset(rt->render_options, RENDER_PATHTRACE))
		ft_printf("current samples number: [%i]\n", kernel->samples_num);
	rt_print_clfloat3(rt->scene.camera.pos, "camera position");
	rt_print_clfloat3(rt->scene.camera.rotation, "camera rotation");
	printf("camera focal distance: [%f]\n",
			rt->scene.camera.focal_distance);
	printf("camera aperture: [%f]\n",
			rt->scene.camera.aperture);
	printf("camera blur strength: [%f]\n",
			rt->scene.camera.blur_strength);
	ft_printf("\033[0m");
}
