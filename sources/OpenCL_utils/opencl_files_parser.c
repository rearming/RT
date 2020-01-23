#include "rt.h"

char			*concat_opencl_kernel_code(int files_nbr, ...)
{
	t_cl_concat_kernel_code		cl_cat;
	int							i;

	i = 0;
	cl_cat.sum_len = 0;
	cl_cat.backup = rt_safe_malloc(1);
	cl_cat.backup[0] = 0;
	va_start(cl_cat.ap, files_nbr);
	while (i < files_nbr)
	{
		cl_cat.fd = open(va_arg(cl_cat.ap, char*), O_RDONLY);
		if (!(cl_cat.str_file = ft_readfile(cl_cat.fd, &cl_cat.file_size)))
			rt_raise_error(ERR_OPENCL_INV_SOURCE_CODE_FILE);
		close(cl_cat.fd);
		cl_cat.sum_len += cl_cat.file_size;
		cl_cat.temp_str = ft_strljoin(cl_cat.backup,
				cl_cat.str_file, cl_cat.sum_len);
		free(cl_cat.str_file);
		free(cl_cat.backup);
		cl_cat.backup = cl_cat.temp_str;
		i++;
	}
	va_end(cl_cat.ap);
	return (cl_cat.backup);
}

char			*get_opencl_kernel_code_text(size_t *out_size)
{
	char		*result_cl_file;
	char		*cl_file;

	cl_file = concat_opencl_kernel_code(15,
			"./sources/OpenCL_kernel_code/opencl_defines.cl",
			"./sources/OpenCL_kernel_code/opencl_structs.cl",
			"./includes/rt_defines.h",
			"./includes/rt_structs.h",
			"./sources/OpenCL_kernel_code/prototypes.cl",
			"./sources/OpenCL_kernel_code/color_utils.cl",
			"./sources/OpenCL_kernel_code/math_utils.cl",
			"./sources/OpenCL_kernel_code/utils.cl",
			"./sources/OpenCL_kernel_code/rt_main.cl",
			"./sources/OpenCL_kernel_code/raytrace.cl",
			"./sources/OpenCL_kernel_code/pathtrace_algo/pathtrace.cl",
			"./sources/OpenCL_kernel_code/pathtrace_algo/pathtrace_utils.cl",
			"./sources/OpenCL_kernel_code/light_computing/light_computing.cl",
			"./sources/OpenCL_kernel_code/object_intersections/intersection_utils.cl",
			"./sources/OpenCL_kernel_code/object_intersections/simple_object_intersections.cl");
	ft_sprintf(&result_cl_file, "%s%s", OPENCL_DEFINES_STR, cl_file);
	*out_size = ft_strlen(result_cl_file);
	free(cl_file);
	return (result_cl_file);
}
