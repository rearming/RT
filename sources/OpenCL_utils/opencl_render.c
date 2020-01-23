#include "rt.h"
#include "../debug/rt_debug_utils.h"
#include "time.h"

// todo отключить передачу g_img_data_float если рейтрейс/etc (не pathtrace)
// можно сделать в то же время, когда будут разделяться кернелы
void		rt_opencl_prepare_memory(t_rt *rt)
{
	g_opencl.opencl_memobj_number = 5;
	rt_opencl_move_host_mem_to_kernel(g_opencl.opencl_memobj_number,
		(t_opencl_mem_obj){&rt->scene,
			sizeof(t_scene), RT_DEFAULT_MEM_FLAG, TRUE},
		(t_opencl_mem_obj){rt->scene.objects,
			sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, FALSE},
		(t_opencl_mem_obj){rt->scene.lights,
			sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, FALSE},
		(t_opencl_mem_obj){&rt->opencl_params,
			sizeof(t_opencl_params), RT_DEFAULT_MEM_FLAG, TRUE},
		(t_opencl_mem_obj){&g_img_data_float,
			sizeof(cl_float3) * WIN_HEIGHT * WIN_WIDTH, RT_MEM_RW_FLAG, FALSE}
			);
}

void		rt_print_opencl_profile_info(void)
{
	clWaitForEvents(1, &g_opencl.profile_event);
	cl_ulong start = 0, end = 0;
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
	clGetEventProfilingInfo(g_opencl.profile_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	cl_double nd_range_pure_exec_time_ms = (cl_double)(end - start) * (cl_double)(1e-06);
	ft_printf("\033[0;91m");
	ft_printf("kernel exec time: [%.2f]\n", nd_range_pure_exec_time_ms);
	ft_printf("\033[0m");
}

t_bool		rt_camera_moved(t_camera *camera)
{
	static t_camera	previous_camera = (t_camera)
			{.pos = (cl_float3){{0, 0, 0}}, .rotation = (cl_float3){{0, 0, 0}}};
	static time_t		prev_time = NOT_SET;
	const time_t		current_time = time(NULL);
	t_bool				is_moved;

	is_moved = !rt_float3_equals(previous_camera.pos, camera->pos) ||
			   !rt_float3_equals(previous_camera.rotation, camera->rotation);
	if (prev_time == NOT_SET)
		prev_time = current_time;
	if (current_time != prev_time)
		previous_camera = *camera;
	if (is_moved)
	{
		previous_camera = *camera;
		prev_time = current_time;
	}
	return (is_moved);
}

void		rt_update_rt_params(t_rt *rt)
{
	if (rt->opencl_params.render_algo == PATH_TRACE)
		rt->opencl_params.pathtrace_params.current_samples_num++;
	else
		rt->opencl_params.pathtrace_params.current_samples_num = 0;
	if (rt_camera_moved(&rt->scene.camera))
		rt->opencl_params.pathtrace_params.current_samples_num = 0;
	rt->opencl_params.seed = drand48();
}

void		rt_opencl_render(t_rt *rt)
{
	const size_t	kernel_num = OPENCL_RELEASE_KERNEL_NUM;
//	const size_t	kernel_num = 50;
//	const size_t	kernel_num = 2;
	int				err;

	rt_opencl_prepare_memory(rt);
	rt_opencl_setup_image_buffer();
	rt_update_rt_params(rt);
	if (rt->events.info)
		rt_print_debug_info(rt);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			g_opencl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, &g_opencl.profile_event);
	if (rt->events.info)
		rt_print_opencl_profile_info();
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
//	//todo обернуть в функцию
	err |= clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
	opencl_clean_memobjs();
}
