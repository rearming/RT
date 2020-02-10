#include "rt.h"
#include "rt_opencl.h"

inline void rt_opencl_setup_image_buffer(t_rt_renderer *renderer)
{
	int				err;
	static bool		image_created = false;

	if (image_created == false)
	{
		g_opencl.img_data_mem = clCreateBuffer(g_opencl.context,
				CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
				sizeof(int) * WIN_HEIGHT * WIN_WIDTH, g_img_data, &err);
		ft_bzero(g_img_data, sizeof(int) * WIN_HEIGHT * WIN_WIDTH);
		rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	}
	err = clSetKernelArg(renderer->kernel, renderer->buffers_num,
						 sizeof(cl_mem), &g_opencl.img_data_mem);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
	image_created = true;
}

/*
**	OpenCL errors
*/

const char	*g_opencl_errors[] =
{
	"CL_SUCCESS",
 	"CL_DEVICE_NOT_FOUND",
 	"CL_DEVICE_NOT_AVAILABLE",
 	"CL_COMPILER_NOT_AVAILABLE",
 	"CL_MEM_OBJECT_ALLOCATION_FAILURE",
 	"CL_OUT_OF_RESOURCES",
 	"CL_OUT_OF_HOST_MEMORY",
 	"CL_PROFILING_INFO_NOT_AVAILABLE",
 	"CL_MEM_COPY_OVERLAP",
 	"CL_IMAGE_FORMAT_MISMATCH",
 	"CL_IMAGE_FORMAT_NOT_SUPPORTED",
 	"CL_BUILD_PROGRAM_FAILURE",
 	"CL_MAP_FAILURE",
 	"CL_MISALIGNED_SUB_BUFFER_OFFSET",
 	"CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST",
 	"CL_COMPILE_PROGRAM_FAILURE",
 	"CL_LINKER_NOT_AVAILABLE",
 	"CL_LINK_PROGRAM_FAILURE",
 	"CL_DEVICE_PARTITION_FAILED",
 	"CL_KERNEL_ARG_INFO_NOT_AVAILABLE",

 	"CL_INVALID_VALUE",
 	"CL_INVALID_DEVICE_TYPE",
 	"CL_INVALID_PLATFORM",
 	"CL_INVALID_DEVICE",
 	"CL_INVALID_CONTEXT",
 	"CL_INVALID_QUEUE_PROPERTIES",
 	"CL_INVALID_COMMAND_QUEUE",
 	"CL_INVALID_HOST_PTR",
 	"CL_INVALID_MEM_OBJECT",
 	"CL_INVALID_IMAGE_FORMAT_DESCRIPTOR",
 	"CL_INVALID_IMAGE_SIZE",
 	"CL_INVALID_SAMPLER",
 	"CL_INVALID_BINARY",
 	"CL_INVALID_BUILD_OPTIONS",
 	"CL_INVALID_PROGRAM",
 	"CL_INVALID_PROGRAM_EXECUTABLE",
 	"CL_INVALID_KERNEL_NAME",
 	"CL_INVALID_KERNEL_DEFINITION",
 	"CL_INVALID_KERNEL",
 	"CL_INVALID_ARG_INDEX",
 	"CL_INVALID_ARG_VALUE",
 	"CL_INVALID_ARG_SIZE",
 	"CL_INVALID_KERNEL_ARGS",
 	"CL_INVALID_WORK_DIMENSION",
 	"CL_INVALID_WORK_GROUP_SIZE",
 	"CL_INVALID_WORK_ITEM_SIZE",
 	"CL_INVALID_GLOBAL_OFFSET",
 	"CL_INVALID_EVENT_WAIT_LIST",
 	"CL_INVALID_EVENT",
 	"CL_INVALID_OPERATION",
 	"CL_INVALID_GL_OBJECT",
 	"CL_INVALID_BUFFER_SIZE",
 	"CL_INVALID_MIP_LEVEL",
 	"CL_INVALID_GLOBAL_WORK_SIZE",
 	"CL_INVALID_PROPERTY",
 	"CL_INVALID_IMAGE_DESCRIPTOR",
 	"CL_INVALID_COMPILER_OPTIONS",
 	"CL_INVALID_LINKER_OPTIONS",
 	"CL_INVALID_DEVICE_PARTITION_COUNT",
};

# define END_OF_FIRST_ERR_PART 19
# define OFFSET_BETWEEN_ERRORS 10

static inline int	rt_opencl_correct_err_code(int opencl_err_code)
{
	opencl_err_code = -opencl_err_code;
	if (opencl_err_code <= END_OF_FIRST_ERR_PART)
		return (opencl_err_code);
	else
		return (opencl_err_code - OFFSET_BETWEEN_ERRORS);
}

inline void		rt_opencl_handle_error(const char *rt_err_str, int opencl_err_code)
{
	if (opencl_err_code != CL_SUCCESS)
	{
		ft_printf_fd(STDERR_FILENO, "OpenCL err code: [%i], %s\n",
				opencl_err_code, g_opencl_errors[rt_opencl_correct_err_code(opencl_err_code)]);
		rt_raise_error(rt_err_str);
	}
}
