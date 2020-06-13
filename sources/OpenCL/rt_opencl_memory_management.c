/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_opencl_memory_management.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_opencl.h"

void		rt_opencl_alloc_buffers(
		uint32_t render_action,
		t_opencl_mem_obj *memobjs)
{
	int					i;
	int					err;

	i = 0;
	if (render_action & ACTION_INIT)
		g_opencl.buffers =
				rt_safe_malloc(g_opencl.buffers_num * sizeof(t_cl_buffer));
	while (i < g_opencl.buffers_num)
	{
		if (memobjs[i].render_action & render_action)
		{
			g_opencl.buffers[i].mem = clCreateBuffer(g_opencl.context,
					memobjs[i].mem_flags, memobjs[i].size, memobjs[i].ptr,
					&err);
			g_opencl.buffers[i].render_action = memobjs[i].render_action;
			rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
		}
		g_opencl.buffers[i].render_action = memobjs[i].render_action;
		i++;
	}
}

void		rt_opencl_release_buffers(uint32_t current_render_action)
{
	int		i;

	i = 0;
	while (i < g_opencl.buffers_num)
	{
		if (g_opencl.buffers[i].render_action & current_render_action
		|| current_render_action & ACTION_EXIT)
			clReleaseMemObject(g_opencl.buffers[i].mem);
		i++;
	}
	if (current_render_action & ACTION_EXIT)
		free(g_opencl.buffers);
}
