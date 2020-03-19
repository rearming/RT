#include "rt.h"
#include "rt_opencl.h"

const t_kernel_info	g_kernels_info[] = {
		(t_kernel_info){
			.kernel_path = "./sources/kernel/post_processing/kernel_depth_of_field.cl",
			.kernel_name = "kernel_depth_of_field"},
		(t_kernel_info){
				.kernel_path = "./sources/kernel/post_processing/kernel_sepia.cl",
				.kernel_name = "kernel_sepia"},
		(t_kernel_info){
				.kernel_path = "./sources/kernel/post_processing/kernel_cartoon.cl",
				.kernel_name = "kernel_cartoon"}
};

void		rt_opencl_compile_kernels(uint32_t render_options)
{
	const size_t	kernels_num = sizeof(g_kernels_info) / sizeof(t_kernel_info);
	size_t			i;

	i = 0;
	g_opencl.kernels = rt_safe_malloc(sizeof(cl_kernel) * kernels_num);
	while (i < kernels_num)
	{
		printf("compiling [%s]\n", g_kernels_info[i].kernel_name);
		rt_opencl_compile_kernel(g_kernels_info[i].kernel_path, g_kernels_info[i].kernel_name,
				rt_get_kernel_compile_options(render_options), &g_opencl.kernels[i]);
		i++;
	}
}

void		rt_set_kernel_args(cl_kernel kernel, int args_num, ...)
{
	va_list			args;
	int				err;
	t_cl_mem_types	arg_type;

	va_start(args, args_num);

	for (int i = 0; i < args_num; ++i)
	{
		arg_type = va_arg(args, t_cl_mem_types);
		err = clSetKernelArg(kernel, i, sizeof(cl_mem), &g_opencl.buffers[arg_type].mem);
		rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
	}
	va_end(args);
}
