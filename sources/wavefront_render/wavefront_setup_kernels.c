#include "rt.h"
#include "rt_opencl.h"
#include "rt_wavefront_render.h"

void		rt_set_kernel_args(cl_kernel kernel, int args_num, ...)
{
	va_list			args;
	int				err = CL_SUCCESS;
	t_cl_mem_types	arg_type;
	va_start(args, args_num);

	for (int i = 0; i < args_num; ++i)
	{
		arg_type = va_arg(args, t_cl_mem_types);
//		printf("i: [%i], buffer's ptr: [%p]\n", i, g_opencl.wf_shared_buffers[arg_type].mem);
		err |= clSetKernelArg(kernel, i, sizeof(cl_mem), &g_opencl.wf_shared_buffers[arg_type].mem);
	}
	va_end(args);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
}

const struct s_kernels_info	g_kernels_info[] = {
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_generate_primary_rays.cl",
				.kernel_name = "kernel_generate_primary_rays"},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_find_intersections.cl",
				.kernel_name = "kernel_find_intersections"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_raytrace_material_compute_light.cl",
				.kernel_name = "kernel_raytrace_material_compute_light"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_material_shade.cl",
				.kernel_name = "kernel_material_shade"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_texture_shade.cl",
				.kernel_name = "kernel_texture_shade"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_skybox_shade.cl",
				.kernel_name = "kernel_skybox_shade"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_fill_img_data.cl",
				.kernel_name = "kernel_fill_img_data"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_anti_aliasing_img_generation.cl",
				.kernel_name = "kernel_anti_aliasing_img_generation"
		},
		(struct s_kernels_info){
				.kernel_path = "sources/kernel/wavefront/kernel_anti_aliasing_rays_generation.cl",
				.kernel_name = "kernel_anti_aliasing_rays_generation"
		}
};

cl_kernel	*g_wavefront_kernels;

void		wavefront_compile_kernels(uint32_t render_flags, t_renderer_params *params)
{
	size_t					i;
	size_t					kernels_num = sizeof(g_kernels_info) / sizeof(struct s_kernels_info);

	rt_init_renderer_params(params);
	i = 0;
	g_wavefront_kernels = rt_safe_malloc(sizeof(cl_kernel) * kernels_num);
	while (i < kernels_num)
	{
		printf("compiling [%s]\n", g_kernels_info[i].kernel_name);
		rt_opencl_create_kernel(
				g_kernels_info[i].kernel_path,
				g_kernels_info[i].kernel_name,
				rt_get_kernel_compile_options(render_flags),
				&g_wavefront_kernels[i]);
		i++;
	}
}
