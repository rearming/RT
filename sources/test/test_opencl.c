#include "test_header.h"

t_opencl	g_opencl;
t_sdl		g_sdl;
int			*g_img_data;

void	test_opencl_create_buffers(void)
{
	int			int_arr_size = 20;
	int			*test_int_arr = test_get_int_arr(int_arr_size);

	int			point_arr_size = 10;
	t_point		*test_point_arr = test_get_point_arr(point_arr_size);

	int 		err;

	g_opencl.opencl_memobj_number = 2;
	g_opencl.opencl_mem = rt_safe_malloc(sizeof(t_opencl_mem_obj));

	g_opencl.opencl_mem[0].mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(int) * int_arr_size, test_int_arr, &err);
	g_opencl.opencl_mem[0].copy_mem = false;
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);

	g_opencl.opencl_mem[1].mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG,
			sizeof(t_point) * point_arr_size, test_point_arr, &err);
	g_opencl.opencl_mem[1].copy_mem = false;
	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);

	g_opencl.img_data_mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE,
			sizeof(int) * WIN_HEIGHT * WIN_WIDTH, g_img_data, &err);

	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);

}

void	test_opencl_setargs(void)
{
	int			err;

	int			int_arr_size = 20;
	int			*test_int_arr = test_get_int_arr(int_arr_size);

	int			point_arr_size = 10;
	t_point		*test_point_arr = test_get_point_arr(point_arr_size);

//	g_opencl.opencl_mem[0].mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG,
//			sizeof(int) * int_arr_size, test_int_arr, &err);
//	g_opencl.opencl_mem[0].copy_mem = true;
//	err != CL_SUCCESS ? rt_raise_error(ERR_OPENCL_CREATE_BUFFER) : 0;

//	g_opencl.opencl_mem[1].mem = clCreateBuffer(g_opencl.context, RT_DEFAULT_MEM_FLAG,
//			sizeof(t_point) * point_arr_size, test_point_arr, &err);
//	g_opencl.opencl_mem[1].copy_mem = false;
//	err != CL_SUCCESS ? rt_raise_error(ERR_OPENCL_CREATE_BUFFER) : 0;

	err = clSetKernelArg(g_opencl.kernel, 0, sizeof(cl_mem), &g_opencl.opencl_mem[0].mem);
	err != CL_SUCCESS ? rt_raise_error(ERR_OPENCL_SETARG) : 0;
	err = clSetKernelArg(g_opencl.kernel, 1, sizeof(cl_mem), &g_opencl.opencl_mem[1].mem);
	err != CL_SUCCESS ? rt_raise_error(ERR_OPENCL_SETARG) : 0;
}

void	test_opencl_init(void)
{
	int			err;

	err = clGetPlatformIDs(1, &g_opencl.platform_id, &g_opencl.ret_num_platforms);
	if (err)
		rt_raise_error(ERR_OPENCL_GET_PLATFORM_ID);
	err = clGetDeviceIDs(g_opencl.platform_id, CL_DEVICE_TYPE_GPU, 1, &g_opencl.device_id, &g_opencl.ret_num_devices);
	if (err)
		rt_raise_error(ERR_OPENCL_GET_DEVICE_ID);
	g_opencl.context = clCreateContext(NULL, 1, &g_opencl.device_id, NULL, NULL, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_CONTEXT);
	g_opencl.queue = clCreateCommandQueue(g_opencl.context, g_opencl.device_id, 0, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_QUEUE);

	char		*opencl_kernel_file;
	size_t		size;

	opencl_kernel_file = ft_read_files(3,
			"./includes/rt_defines.h",
			"./includes/rt_structs.h",
			"./sources/test/test_kernel.cl");
	ft_sprintf(&opencl_kernel_file, "%s%s", OPENCL_APPLE_DEFINE, opencl_kernel_file);

	g_opencl.program = clCreateProgramWithSource(g_opencl.context, 1, (const char **)&opencl_kernel_file, &size, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_PROGRAM);
	if ((err = clBuildProgram(g_opencl.program, 1, &g_opencl.device_id, NULL, NULL, NULL)))
	{
		print_cl_build_program_debug();
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	g_opencl.kernel = clCreateKernel(g_opencl.program, "test_kernel", &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_KERNEL);

	test_opencl_create_buffers();
}

void 	test_run_kernels(t_rt *rt)
{
	int err;

	test_opencl_setargs();

//	g_opencl.img_data_mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE,
//			sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
//	rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);

	err = clSetKernelArg(g_opencl.kernel, g_opencl.opencl_memobj_number,
			sizeof(cl_mem), &g_opencl.img_data_mem);
	if (err)
		rt_raise_error(ERR_OPENCL_SETARG);

	const size_t	kernel_num = OPENCL_RELEASE_KERNEL_NUM;

	err = clEnqueueNDRangeKernel(g_opencl.queue, g_opencl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, NULL);

	if (err)
		rt_raise_error(ERR_OPENCL_RUN_KERNELS);

	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT, g_img_data, 0, NULL, NULL);
	if (err)
	{
		printf("opencl err code: [%i]\n", err);
		rt_raise_error(ERR_OPENCL_READ_BUFFER);
	}

	opencl_clean_memobjs();
}

void	rt_test_opencl(void)
{
	rt_sdl_init();
	test_opencl_init();

//	rt_render(NULL, &fill_all_g_img_data);
	rt_render(NULL, &test_run_kernels);
//	rt_render(NULL, &test_run_kernels);
//	rt_render(NULL, &test_run_kernels);
	test_rt_loop(NULL);
}
