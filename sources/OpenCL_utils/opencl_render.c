#include "rt.h"

void		rt_opencl_prepare_memory(t_rt *rt)
{
	g_opencl.opencl_memobj_number = 4;
	rt_opencl_move_host_mem_to_kernel(g_opencl.opencl_memobj_number,
		(t_opencl_mem_obj){&rt->scene,
			sizeof(t_scene), RT_DEFAULT_MEM_FLAG, TRUE},
		(t_opencl_mem_obj){rt->scene.objects,
			sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, FALSE},
		(t_opencl_mem_obj){rt->scene.lights,
			sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, FALSE},
		(t_opencl_mem_obj){&rt->opencl_params,
			sizeof(t_opencl_params), RT_DEFAULT_MEM_FLAG, TRUE}
			);
}

void		rt_opencl_profile(void)
{
	clWaitForEvents(1, &g_opencl.profile_event);
	cl_ulong start = 0, end = 0;
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	cl_double nd_range_pure_exec_time_ms = (cl_double)(end - start) * (cl_double)(1e-06);
	ft_printf("kernel exec time: [%f]\n", nd_range_pure_exec_time_ms);
}

void		rt_update_opecnl_params(t_opencl_params *opencl_params)
{
	if (opencl_params->render_algo == PATHTRACE)
		opencl_params->pathtrace_params.current_samples_num++;
	else
		opencl_params->pathtrace_params.current_samples_num = 1;
	opencl_params->randoms = arc4random();
}

void		rt_opencl_render(t_rt *rt)
{
	const size_t	kernel_num = OPENCL_RELEASE_KERNEL_NUM;
//	const size_t	kernel_num = 50;
	int				err;

	rt_opencl_prepare_memory(rt);
	rt_opencl_setup_image_buffer();
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			g_opencl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_profile();
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	opencl_clean_memobjs();
	rt_update_opecnl_params(&rt->opencl_params);
}
