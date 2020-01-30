#include "rt.h"

char			*get_opencl_kernel_code_text(size_t *out_size)
{
	char		*result_cl_file;
	char		*cl_file;

	cl_file = ft_read_files(18,
			"./sources/OpenCL_kernel_code/opencl_defines.cl",
			"./sources/OpenCL_kernel_code/opencl_structs.cl",
			"./includes/rt_defines.h",
			"./includes/rt_structs.h",
			"./sources/OpenCL_kernel_code/prototypes.cl",
			"./sources/OpenCL_kernel_code/color_utils.cl",
			"./sources/OpenCL_kernel_code/math_utils.cl",
			"./sources/OpenCL_kernel_code/raytrace.cl",
			"./sources/OpenCL_kernel_code/rt_main.cl",
			"./sources/OpenCL_kernel_code/utils.cl",
			"./sources/OpenCL_kernel_code/light_computing/light_computing.cl",
			"./sources/OpenCL_kernel_code/object_intersections/intersection_utils.cl",
			"./sources/OpenCL_kernel_code/object_intersections/mesh_intersection.cl",
			"./sources/OpenCL_kernel_code/object_intersections/ray_trianlge_intersection.cl",
			"./sources/OpenCL_kernel_code/object_intersections/simple_object_intersections.cl",
			"./sources/OpenCL_kernel_code/pathtrace_algo/pathtrace.cl",
			"./sources/OpenCL_kernel_code/pathtrace_algo/pathtrace_utils.cl",
			"./sources/OpenCL_kernel_code/pathtrace_algo/shade_pathtrace.cl");
	ft_sprintf(&result_cl_file, "%s%s", OPENCL_DEFINES_STR, cl_file);
	*out_size = ft_strlen(result_cl_file);
	free(cl_file);
	return (result_cl_file);
}
