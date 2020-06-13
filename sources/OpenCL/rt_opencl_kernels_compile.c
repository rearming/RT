/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_opencl_kernels_compile.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_opencl.h"

const t_kernel_info	g_kernels_info[] =
{
	(t_kernel_info){
		.kernel_path =
		"./sources/kernel/post_processing/kernel_depth_of_field.cl",
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
	const size_t	kern_num = sizeof(g_kernels_info) / sizeof(t_kernel_info);
	size_t			i;

	i = 0;
	g_opencl.kernels = rt_safe_malloc(sizeof(cl_kernel) * kern_num);
	while (i < kern_num)
	{
		rt_opencl_compile_kernel(g_kernels_info[i].kernel_path,
				g_kernels_info[i].kernel_name,
				rt_get_kernel_compile_options(render_options),
				&g_opencl.kernels[i]);
		i++;
	}
}

void		rt_set_kernel_args(cl_kernel kernel, int args_num, ...)
{
	va_list			args;
	int				err;
	t_cl_mem_types	arg_type;
	int				i;

	i = 0;
	va_start(args, args_num);
	while (i < args_num)
	{
		arg_type = va_arg(args, t_cl_mem_types);
		err = clSetKernelArg(kernel, i, sizeof(cl_mem),
				&g_opencl.buffers[arg_type].mem);
		rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
		i++;
	}
	va_end(args);
}
