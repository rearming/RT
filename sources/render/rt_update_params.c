/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_update_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	render_kernel_reset_samples(t_list *list)
{
	((t_render_kernel*)list->content)->samples_num = 0;
}

void	rt_update_render_params(
		t_render_kernel *render_kernel,
		t_render_params *params,
		uint32_t render_options,
		uint32_t render_action)
{
	if (rt_bit_isset(render_options, RENDER_PATHTRACE))
	{
		params->seed = drand48();
		params->pathtrace_params.current_samples_num =
				render_kernel->samples_num;
		render_kernel->samples_num++;
	}
	if (rt_bit_isset(render_action, ACTION_CAMERA_CHANGED))
		ft_lstmap(g_opencl.render_kernels, &render_kernel_reset_samples);
}
