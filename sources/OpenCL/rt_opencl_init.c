/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_opencl_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "rt.h"
#include "rt_opencl.h"

static void		release_resources(
		cl_program program,
		char *opencl_kernel_code,
		const char *compile_options)
{
	int		err;

	err = clReleaseProgram(program);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_PROGRAM, err);
	free(opencl_kernel_code);
	free((char*)compile_options);
}

void			rt_opencl_compile_kernel(
		const char *kernel_path,
		const char *kernel_name,
		const char *compile_options,
		cl_kernel *out_kernel)
{
	static size_t	size = 0;
	char			*opencl_kernel_code;
	cl_program		program;
	int				err;
	const clock_t	start = clock();

	opencl_kernel_code = get_opencl_kernel_code_text(kernel_path, &size);
	program = clCreateProgramWithSource(g_opencl.context, 1,
			(const char **)&opencl_kernel_code, &size, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_PROGRAM, err);
	if ((err = clBuildProgram(
			program, 1, &g_opencl.device_id, compile_options, NULL, NULL)))
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	*out_kernel = clCreateKernel(program, kernel_name, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_KERNEL, err);
	printf("kernel [%s] compiled with options [%s] in [%.3f] sec.\n",
			kernel_name, compile_options,
			(double)(clock() - start) / CLOCKS_PER_SEC);
	release_resources(program, opencl_kernel_code, compile_options);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void			rt_opencl_init(void)
{
	int			err;

	setenv("CUDA_CACHE_DISABLE", "1", 1);
	err = clGetPlatformIDs(
			1, &g_opencl.platform_id, &g_opencl.ret_num_platforms);
	rt_opencl_handle_error(ERR_OPENCL_GET_PLATFORM_ID, err);
	err = clGetDeviceIDs(
			g_opencl.platform_id, CL_DEVICE_TYPE_GPU, 1,
			&g_opencl.device_id, &g_opencl.ret_num_devices);
	rt_opencl_handle_error(ERR_OPENCL_GET_DEVICE_ID, err);
	g_opencl.context = clCreateContext(
			NULL, 1, &g_opencl.device_id, NULL, NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_CONTEXT, err);
	g_opencl.queue = clCreateCommandQueue(
			g_opencl.context, g_opencl.device_id, 0, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_QUEUE, err);
	g_opencl.render_kernels = NULL;
}

#pragma clang diagnostic pop
