#include "rt.h"
#include "rt_opencl.h"

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
				NULL
		};

char				*rt_get_kernel_compile_options(uint32_t flags)
{
	char		*options;
	char		*tmp;
	uint32_t	mask;
	int			i;

	i = 0;
	options = rt_safe_malloc(1);
	options[0] = 0;
	mask = 1;
	while (i < (int)sizeof(g_opencl_defines) / (int)sizeof(char*))
	{
		tmp = ft_strjoin(options, (flags & mask) ? g_opencl_defines[i] : "");
		free(options);
		options = tmp;
		mask <<= 1;
		i++;
	}
	return (options);
}

static cl_mem	alloc_float3_img_buffer(void)
{
	int		err;
	cl_mem	mem;

	mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE, sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT, NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	return (mem);
}

t_render_kernel *rt_create_render_kernel(uint32_t options)
{
	t_render_kernel	*new_kernel;
	const char		*opencl_defines = rt_get_kernel_compile_options(options);
	char			*compile_options;
	char			*temp_str;

	new_kernel = rt_safe_malloc(sizeof(t_render_kernel));
	new_kernel->options = options;
	ft_sprintf(&temp_str, "%s %s", OPENCL_INCLUDE_DIRS, opencl_defines);
	compile_options = ft_del_whitespaces(temp_str);
	ft_printf("compile options: %s\n", opencl_defines);
	rt_opencl_create_kernel(compile_options, &new_kernel->kernel);
	new_kernel->img_data_float = alloc_float3_img_buffer();
	free((char*)opencl_defines);
	free(compile_options);
	free(temp_str);
	return (new_kernel);
}

t_render_kernel *rt_get_render_kernel(uint32_t options)
{
	t_list			*tmp_kernel;

	tmp_kernel = g_opencl.kernels;
	while (tmp_kernel)
	{
		if (((t_render_kernel*)tmp_kernel->content)->options == options)
			return (tmp_kernel->content);
		tmp_kernel = tmp_kernel->next;
	}
	ft_lstaddback_p(&g_opencl.kernels, rt_create_render_kernel(options), sizeof(t_render_kernel));
	return (g_opencl.kernels->last->content);
}
