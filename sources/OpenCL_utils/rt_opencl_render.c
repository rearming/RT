#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"
#include "rt_events.h"

void		set_render_kernel_args(t_render_kernel *render_kernel)
{
	int		args_num = 17;
	int		err;

	rt_set_kernel_args(render_kernel->kernel, args_num,
			RT_CL_MEM_SCENE, RT_CL_MEM_OBJECTS, RT_CL_MEM_LIGHTS, RT_CL_MEM_PARAMS,
			RT_CL_MEM_KD_INFO, RT_CL_MEM_KD_TREE, RT_CL_MEM_KD_INDICES,
			RT_CL_MEM_MESHES_INFO, RT_CL_MEM_POLYGONS, RT_CL_MEM_VERTICES,
			RT_CL_MEM_V_NORMALS, RT_CL_MEM_V_TEXTURES,
			RT_CL_MEM_TEXTURE_INFO, RT_CL_MEM_TEXTURE_LIST,
			RT_CL_MEM_SKYBOX_INFO, RT_CL_MEM_SKYBOX_LIST,
			RT_CL_MEM_IMG_DATA);
	err = clSetKernelArg(render_kernel->kernel, args_num, sizeof(cl_mem), &render_kernel->img_data_float);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
}

void		run_render_kernel(t_rt *rt, t_render_kernel *render_kernel, const size_t *work_size)
{
	int			err;

	rt_update_render_params(render_kernel, &rt->params, rt->render_options, rt->render_actions);
	set_render_kernel_args(render_kernel);
	if (rt_bit_isset(rt->events, EVENT_INFO))
		rt_print_debug_info(rt, render_kernel);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			render_kernel->kernel, 1, NULL, work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt_bit_isset(rt->events, EVENT_INFO))
		rt_print_opencl_profile_info();
	err = clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_EVENT, err);
	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.buffers[RT_CL_MEM_IMG_DATA].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT, g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void		run_blur_kernel(t_rt *rt, cl_kernel kernel, const size_t *work_size)
{
	int		err;

	rt_set_kernel_args(kernel, 2, RT_CL_MEM_IMG_DATA, RT_CL_MEM_OUT_IMG_DATA);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err = clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_EVENT, err);

	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.buffers[RT_CL_MEM_OUT_IMG_DATA].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT, g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void		run_sepia_kernel(t_rt *rt, cl_kernel kernel, const size_t *work_size)
{
	int		err;

	rt_set_kernel_args(kernel, 2, RT_CL_MEM_IMG_DATA, RT_CL_MEM_OUT_IMG_DATA); // тут надо будет делать swap

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err = clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_EVENT, err);

	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.buffers[RT_CL_MEM_OUT_IMG_DATA].mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT, g_img_data, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);
}

void		rt_opencl_render(void *rt_ptr)
{
	const size_t		global_work_size[1] = {WIN_WIDTH * WIN_HEIGHT};
	t_rt				*rt;

	rt = rt_ptr;
	if (!rt_bit_isset(rt->render_actions, ACTION_INIT))
		rt_opencl_release_buffers(rt->render_actions);
	else
		rt_opencl_compile_kernels(rt->render_options);
	rt_opencl_prepare_memory(rt, rt->render_actions);
	run_render_kernel(rt, rt_get_render_kernel(rt->render_options), global_work_size);
	run_blur_kernel(rt, g_opencl.kernels[KERNEL_GAUSS_BLUR], global_work_size);
//	run_sepia_kernel(rt, g_opencl.kernels[KERNEL_SEPIA], global_work_size);
	rt->render_actions &= ACTION_PATHTRACE;
}
