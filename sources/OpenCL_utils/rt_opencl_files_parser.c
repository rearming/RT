#include "rt.h"

char			*get_opencl_kernel_code_text(size_t *out_size)
{
	char		*result_cl_file;
	char		*cl_file;

	cl_file = ft_readfile(open("./sources/kernel/rt_main.cl", O_RDONLY), out_size, 10000);
	ft_sprintf(&result_cl_file, "%s%s", OPENCL_APPLE_DEFINE, cl_file);
	*out_size = ft_strlen(result_cl_file);
	free(cl_file);
	return (result_cl_file);
}
