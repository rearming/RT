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
				" -D RENDER_ANTI_ALIASING ",
				NULL
		};

char				*rt_get_kernel_compile_defines(uint32_t flags)
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

char				*rt_get_kernel_compile_options(uint32_t flags)
{
	const char		*opencl_defines = rt_get_kernel_compile_defines(flags);
	char			*temp_str;
	char			*compile_options;

	ft_sprintf(&temp_str, "%s %s", OPENCL_INCLUDE_DIRS, opencl_defines);
	compile_options = ft_del_whitespaces(temp_str);
	ft_printf("compile options: %s\n", opencl_defines);
	free((char*)opencl_defines);
	free(temp_str);
	return (compile_options);
}

t_rt_renderer		*rt_create_renderer(uint32_t flags)
{
	t_rt_renderer	*new_renderer;
	char			*compile_options = rt_get_kernel_compile_options(flags);

	new_renderer = rt_safe_malloc(sizeof(t_rt_renderer));
	new_renderer->flags = flags;
	new_renderer->copy_done = false;
	new_renderer->primary_img = NULL;
	new_renderer->rays_buffer = NULL;
	rt_init_renderer_params(&new_renderer->params);
	rt_opencl_create_kernel(IMG_GEN_KERNEL_PATH, IMG_GEN_KERNEL_NAME,
			compile_options,
			&new_renderer->img_gen_kernel);
	rt_opencl_create_kernel(RAYS_GEN_KERNEL_PATH, RAYS_GEN_KERNEL_NAME,
			compile_options,
			&new_renderer->ray_gen_kernel);
	rt_opencl_create_kernel(MAIN_KERNEL_PATH, MAIN_KERNEL_NAME, compile_options,
			&new_renderer->main_kernel);
	free(compile_options);
	return (new_renderer);
}

t_rt_renderer		*rt_get_renderer(uint32_t flags)
{
	t_list			*tmp_renderer;

	tmp_renderer = g_opencl.renderers;
	while (tmp_renderer)
	{
		if (((t_rt_renderer*)tmp_renderer->content)->flags == flags)
			return (tmp_renderer->content);
		tmp_renderer = tmp_renderer->next;
	}
	ft_lstaddback_p(&g_opencl.renderers, rt_create_renderer(flags), sizeof(t_rt_renderer));
	return (g_opencl.renderers->last->content);
}
