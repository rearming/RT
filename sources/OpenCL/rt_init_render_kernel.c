/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_render_kernel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_opencl.h"
#include "rt_window_params.h"

const char	*g_opencl_defines[] =
{
	" -D RENDER_RAYTRACE ",
	" -D RENDER_PATHTRACE ",
	" -D RENDER_RAYMARCH",
	" -D RENDER_MESH ",
	" -D RENDER_BACKFACE_CULLING ",
	" -D RENDER_OBJECTS ",
	" -D RENDER_MESH_VTEXTURES ",
	" -D RENDER_TEXTURES ",
	" -D RENDER_ANTI_ALIASING",
	" -D RENDER_SMOOTH_NORMALS",
	" -D RENDER_SKYBOX",
	" -D RENDER_IMPRESSIVE",
	NULL
};

#define FUCK_NORME CL_MEM_READ_WRITE

static cl_mem	alloc_float3_img_buffer(void)
{
	int		err;
	cl_mem	mem;

	mem = clCreateBuffer(g_opencl.context, FUCK_NORME,
			WIN_WIDTH * WIN_HEIGHT * sizeof(cl_float3), NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	return (mem);
}

char			*rt_get_kernel_compile_defines(uint32_t options)
{
	char		*str_options;
	char		*tmp;
	uint32_t	mask;
	int			i;

	i = 0;
	str_options = rt_safe_malloc(1);
	str_options[0] = 0;
	mask = 1;
	while (i < (int)sizeof(g_opencl_defines) / (int)sizeof(char*))
	{
		tmp = ft_strjoin(str_options,
				(options & mask) ? g_opencl_defines[i] : "");
		free(str_options);
		str_options = tmp;
		mask <<= 1;
		i++;
	}
	return (str_options);
}

char *rt_get_kernel_compile_options(uint32_t options, bool includes_only)
{
	const char		*opencl_defines = rt_get_kernel_compile_defines(options);
	char			*temp_str;
	char			*compile_options;

	if (includes_only)
		ft_sprintf(&temp_str, "%s", OPENCL_INCLUDE_DIRS);
	else
		ft_sprintf(&temp_str, "%s %s", OPENCL_INCLUDE_DIRS, opencl_defines);
	compile_options = ft_del_whitespaces(temp_str);
	free((char*)opencl_defines);
	free(temp_str);
	return (compile_options);
}

t_render_kernel	*rt_create_render_kernel(uint32_t options)
{
	t_render_kernel		*new_kernel;

	new_kernel = rt_safe_malloc(sizeof(t_render_kernel));
	new_kernel->options = options;
	rt_opencl_compile_kernel(RENDER_KERNEL_PATH, RENDER_KERNEL_NAME,
			rt_get_kernel_compile_options(options, false), &new_kernel->kernel);
	new_kernel->img_data_float = alloc_float3_img_buffer();
	new_kernel->samples_num = 0;
	return (new_kernel);
}

t_render_kernel	*rt_get_render_kernel(uint32_t options)
{
	t_list			*tmp_kernel;

	tmp_kernel = g_opencl.render_kernels;
	while (tmp_kernel)
	{
		if (((t_render_kernel*)tmp_kernel->content)->options == options)
			return (tmp_kernel->content);
		tmp_kernel = tmp_kernel->next;
	}
	ft_lstaddback_p(&g_opencl.render_kernels,
			rt_create_render_kernel(options), sizeof(t_render_kernel));
	return (g_opencl.render_kernels->last->content);
}
