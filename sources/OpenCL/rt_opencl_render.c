/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_opencl_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_opencl.h"
#include "rt_window_params.h"

void		rt_read_img_buffer(void)
{
	int		err;

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.buffers[switch_img_buffers(NULL, NULL)].mem, CL_TRUE, 0,
			WIN_WIDTH * WIN_HEIGHT * sizeof(int), g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void		rt_opencl_render(void *rt_ptr)
{
	const size_t		work_size[1] = {WIN_WIDTH * WIN_HEIGHT};
	t_rt				*rt;

	rt = rt_ptr;
	if (!rt_bit_isset(rt->render_actions, ACTION_INIT))
		rt_opencl_release_buffers(rt->render_actions);
	else
		rt_opencl_compile_kernels(rt->render_options);
	rt_opencl_prepare_memory(rt, rt->render_actions);
	exec_render_kernel(rt, rt_get_render_kernel(rt->render_options), work_size);
	exec_depth_of_field_kernel(rt, g_opencl.kernels[KERNEL_DOF], work_size);
	exec_sepia_kernel(rt, g_opencl.kernels[KERNEL_SEPIA], work_size);
	exec_cartoon_kernel(rt, g_opencl.kernels[KERNEL_CARTOON], work_size);
	rt_read_img_buffer();
	rt->render_actions &= ACTION_PATHTRACE;
}
