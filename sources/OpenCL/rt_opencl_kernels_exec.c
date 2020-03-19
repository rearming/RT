#include "rt.h"
#include "rt_opencl.h"
#include "rt_opencl_params_defines.h"
#include "rt_events.h"
#include "rt_debug.h"

void		exec_render_kernel(t_rt *rt, t_render_kernel *render_kernel, const size_t *work_size)
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
}

void		exec_depth_of_field_kernel(t_rt *rt, cl_kernel kernel, const size_t *work_size)
{
	int		err;
	int		in_img_buffer;
	int		out_img_buffer;

	if (!(rt->render_state & STATE_POSTPROCESS_DOF))
		return;
	switch_img_buffers(&in_img_buffer, &out_img_buffer);
	rt_set_kernel_args(kernel, 4,
			RT_CL_MEM_CAMERA, in_img_buffer, RT_CL_MEM_DEPTH_BUFFER,
			out_img_buffer);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err = clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_EVENT, err);
}

void		exec_sepia_kernel(t_rt *rt, cl_kernel kernel, const size_t *work_size)
{
	int		err;
	int		in_img_buffer;
	int		out_img_buffer;

	if (!(rt->render_state & STATE_POSTPROCESS_SEPIA))
		return;
	switch_img_buffers(&in_img_buffer, &out_img_buffer);
	rt_set_kernel_args(kernel, 2, in_img_buffer, out_img_buffer);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err = clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_EVENT, err);
}

void		exec_cartoon_kernel(t_rt *rt, cl_kernel kernel, const size_t *work_size)
{
	int		err;
	int		in_img_buffer;
	int		out_img_buffer;

	if (!(rt->render_state & STATE_POSTPROCESS_CARTOON))
		return;
	switch_img_buffers(&in_img_buffer, &out_img_buffer);
	rt_set_kernel_args(kernel, 2, in_img_buffer, out_img_buffer);
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			kernel, 1, NULL, work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	err = clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RELEASE_EVENT, err);
}

