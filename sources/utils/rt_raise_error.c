#include "libft.h"
#include "rt_errors.h"

static void		raise_error2(int err_code)
{
	if (err_code == ERR_OPENCL_BUILD_PROGRAM)
		ft_printf_fd(STDERR_FILENO, "clBuildProgram failed\n");
	else if (err_code == ERR_OPENCL_CREATE_KERNEL)
		ft_printf_fd(STDERR_FILENO, "clCreateKernel failed\n");
	else if (err_code == ERR_OPENCL_CREATE_BUFFER)
		ft_printf_fd(STDERR_FILENO, "clCreateBuffer failed\n");
	else if (err_code == ERR_OPENCL_SETARG)
		ft_printf_fd(STDERR_FILENO, "clSetKernelArg failed\n");
	else if (err_code == ERR_OPENCL_INV_SOURCE_CODE_FILE)
		ft_printf_fd(STDERR_FILENO, "error when reading opencl "
						"source code file\n");
	else if (err_code == ERR_OPENCL_RUN_KERNELS)
		ft_printf_fd(STDERR_FILENO, "clEnqueueNDRangeKernel failed\n");
	else if (err_code == ERR_OPENCL_READ_BUFFER)
		ft_printf_fd(STDERR_FILENO, "clEnqueueReadBuffer failed\n");
	else if (err_code == ERR_INVALID_TEXRTURE_DIR)
		ft_printf_fd(STDERR_FILENO, "couldn't open dir with textures\n");
	else
		ft_printf_fd(STDERR_FILENO, "UNKNOWN ERROR!\n");
}

void			rt_raise_error(int err_code)
{
	if (err_code == ERR_SDL_INIT)
		ft_printf_fd(STDERR_FILENO, "SDL_Init failed.\n");
	else if (err_code == ERR_SDL_WIN)
		ft_printf_fd(STDERR_FILENO, "SDL_Create_Window failed.\n");
	else if (err_code == ERR_SDL_RENDER)
		ft_printf_fd(STDERR_FILENO, "SDL_Create_Renderer failed.\n");
	else if (err_code == ERR_SDL_TEXTURE_CREATE)
		ft_printf_fd(STDERR_FILENO, "SDL_Create_Texture failed.\n");
	else if (err_code == ERR_MALLOC)
		ft_printf_fd(STDERR_FILENO, "malloc() failed!\n");
	else if (err_code == ERR_OPENCL)
		ft_printf_fd(STDERR_FILENO, "something went wrong in OpenCL!\n");
	else if (err_code == ERR_OPENCL_GET_PLATFORM_ID)
		ft_printf_fd(STDERR_FILENO, "clGetPlatformIDs failed!\n");
	else if (err_code == ERR_OPENCL_GET_DEVICE_ID)
		ft_printf_fd(STDERR_FILENO, "clGetDeviceIDs failed!\n");
	else if (err_code == ERR_OPENCL_CREATE_CONTEXT)
		ft_printf_fd(STDERR_FILENO, "clCreateContext failed!\n");
	else if (err_code == ERR_OPENCL_CREATE_QUEUE)
		ft_printf_fd(STDERR_FILENO, "clCreateCommandQueue failed\n");
	else if (err_code == ERR_OPENCL_CREATE_PROGRAM)
		ft_printf_fd(STDERR_FILENO, "clCreateProgramWithSource failed\n");
	raise_error2(err_code);
	exit(err_code);
}
