#include "rt.h"

static char		*concat_opencl_kernel_code(int files_nbr, ...)
{
	t_cl_gnl	gnl;
	va_list		ap;
	char		*str_file;
	size_t		out_file_size;
	int			i;

	i = 0;
	gnl.sum_len = 0;
	gnl.backup = rt_safe_malloc(1);
	gnl.backup[0] = 0;
	va_start(ap, files_nbr);
	while (i < files_nbr)
	{
		if (!(str_file = ft_readfile(
				open(va_arg(ap, char*), O_RDONLY), &out_file_size)))
			rt_raise_error(ERR_OPENCL_INV_SOURCE_CODE_FILE);
		gnl.sum_len += out_file_size;
		gnl.temp_str = ft_strljoin(gnl.backup, str_file, gnl.sum_len);
		free(str_file);
		free(gnl.backup);
		gnl.backup = gnl.temp_str;
		i++;
	}
	va_end(ap);
	return (gnl.backup);
}

#ifdef __APPLE__
# define OPENCL_DEFINES_STR "#define FT_OPENCL___\n #define __APPLE__\n\n"
#else
# define OPENCL_DEFINES_STR "#define FT_OPENCL___\n\n"
#endif

char			*get_opencl_kernel_code_text(size_t *out_size)
{
	char		*result_cl_file;
	char		*cl_file;

	cl_file = concat_opencl_kernel_code(6,
			"./includes/rt_defines.h",
			"./includes/rt_structs.h",
			"./sources/OpenCL_kernel_code/prototypes.cl",
			"./sources/OpenCL_kernel_code/rt_main.cl",
			"./sources/OpenCL_kernel_code/object_intersections/simple_object_intersections.cl",
			"./sources/OpenCL_kernel_code/pathtrace_algo/pathtrace.cl");
	ft_sprintf(&result_cl_file, "%s%s", OPENCL_DEFINES_STR, cl_file);
	*out_size = ft_strlen(result_cl_file);
	free(cl_file);
	return (result_cl_file);
}
