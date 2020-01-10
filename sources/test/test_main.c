#include "rt.h"

t_opencl	g_opencl;
t_sdl		g_sdl;
int			*g_img_data;

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

	opencl_kernel_file =
			"__kernel void\trt_main(\n"
			"    __global int *img_data)\n"
			"{\n"
			"	int		g_id = get_global_id(0);\n"
			"\n"
			"//\tprintf(\"img_data: [%p]\\n\", img_data);\n"
			"}";

	g_opencl.program = clCreateProgramWithSource(g_opencl.context, 1, (const char **)&opencl_kernel_file, &size, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_PROGRAM);
	if ((err = clBuildProgram(g_opencl.program, 1, &g_opencl.device_id, NULL, NULL, NULL)))
	{
		print_cl_build_program_debug();
		rt_raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	g_opencl.kernel = clCreateKernel(g_opencl.program, OPENCL_KERNEL_NAME, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_KERNEL);

	g_opencl.opencl_memobj_number = 0;
}

void 	test_run_kernels(t_rt *rt)
{
	int err;

	printf("test run kernels!\n");
	g_opencl.img_data_mem = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE, sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
	if (err)
		rt_raise_error(ERR_OPENCL_CREATE_BUFFER);

	err = clSetKernelArg(g_opencl.kernel, g_opencl.opencl_memobj_number,
			sizeof(cl_mem), &g_opencl.img_data_mem);
	if (err)
		rt_raise_error(ERR_OPENCL_SETARG);

	const size_t	kernel_num = OPENCL_KERNEL_NUM;

	err = clEnqueueNDRangeKernel(g_opencl.queue, g_opencl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, NULL);

	if (err)
		rt_raise_error(ERR_OPENCL_RUN_KERNELS);

//	int *out_img_data = rt_safe_malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0, sizeof(int) * WIN_WIDTH * WIN_HEIGHT, g_img_data, 0, NULL, NULL);
	if (err)
	{
		printf("opencl err code: [%i]\n", err);
		rt_raise_error(ERR_OPENCL_READ_BUFFER);
	}

	opencl_clean_memobjs();
}

void 	dummy_func(t_rt *rt)
{
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
	{
		g_img_data[i] = COL_GREEN;
	}
}

int		main(int argc, char **argv)
{
	RT_UNUSED(argc);
	RT_UNUSED(argv);
	rt_sdl_init();
	test_opencl_init();
//	rt_render(NULL, &dummy_func);
	rt_render(NULL, &test_run_kernels);
	rt_render(NULL, &test_run_kernels);
	rt_render(NULL, &test_run_kernels);
	rt_loop(NULL);
	return (0);
}
