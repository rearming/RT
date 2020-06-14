/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_opencl_cache_program.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <sys/stat.h>
#include "rt_opencl.h"

static char			*get_opencl_binary_path(
		const char *kernel_name,
		const char *compile_options)
{
	char	*binary_path;

	ft_sprintf(&binary_path, "%s/%s_%zu.%s", RT_OCL_BINARY_DIR, kernel_name,
			rt_hash(compile_options), RT_OCL_BINARY_EXT);
	return (binary_path);
}

static char			*save_program_binary(
		cl_program source_program,
		size_t *binary_size,
		const char *binary_path)
{
	char	*binary;
	FILE	*f;

	clGetProgramInfo(source_program, CL_PROGRAM_BINARY_SIZES,
			sizeof(size_t), binary_size, NULL);
	binary = rt_safe_malloc(*binary_size);
	clGetProgramInfo(source_program, CL_PROGRAM_BINARIES,
			*binary_size, &binary, NULL);
	mkdir(RT_OCL_BINARY_DIR, 0700);
	f = fopen(binary_path, "w");
	fwrite(binary, *binary_size, 1, f);
	fclose(f);
	return (binary);
}

static char			*get_program_binary(
		const char *kernel_path,
		const char *compile_options,
		size_t *out_binary_size,
		const char *binary_path)
{
	char		*binary;
	char		*source_code;
	cl_program	program;
	cl_int		err;

	source_code = get_opencl_kernel_code_text(kernel_path, NULL);
	program = clCreateProgramWithSource(
			g_opencl.context, 1, (const char **)&source_code, NULL, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_FROM_SOURCE, err);
	if (clBuildProgram(
			program, 1, &g_opencl.device_id, compile_options, NULL, NULL))
	{
		print_cl_build_program_debug(program);
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	binary = save_program_binary(program, out_binary_size, binary_path);
	free(source_code);
	return (binary);
}

cl_program			rt_get_cached_cl_program(
		const char *kernel_path,
		const char *kernel_name,
		const char *compile_options)
{
	char		*binary;
	char		*binary_path;
	size_t		binary_size;
	cl_program	program;
	cl_int		err;

	binary_path = get_opencl_binary_path(kernel_name, compile_options);
	if (!(binary = rt_common_read_file(binary_path, &binary_size)))
	{
		ft_printf("compiling opencl binary [%s]\n", binary_path);
		binary = get_program_binary(
				kernel_path, compile_options, &binary_size, binary_path);
	}
	program = clCreateProgramWithBinary(
			g_opencl.context, 1, &g_opencl.device_id, &binary_size,
			(const unsigned char **)&binary, &err, &err);
	rt_opencl_handle_error(ERR_OPENCL_CREATE_FROM_BINARY, err);
	free(binary);
	free(binary_path);
	return (program);
}
