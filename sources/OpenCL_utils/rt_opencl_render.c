#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"

void		rt_setup_rays_gen_kernel(t_rt *rt, t_rt_renderer *renderer)
{
	int				err;

	if (renderer->rays_buffer == NULL)
	{
		renderer->rays_buffer = clCreateBuffer(g_opencl.context,
				CL_MEM_READ_WRITE, sizeof(t_ray) * RAYS_CHUNK_SIZE * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
		rt_opencl_handle_error(ERR_OPENCL_CREATE_BUFFER, err);
	}

	err = clSetKernelArg(renderer->ray_gen_kernel, 0,
			sizeof(cl_mem), &renderer->buffers[0].mem); /// buffers[0] - t_scene* с камерой (нужна для генерации лучей)
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clSetKernelArg(renderer->ray_gen_kernel, 1,
			sizeof(cl_mem), &renderer->primary_img);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clSetKernelArg(renderer->ray_gen_kernel, 2,
			sizeof(cl_mem), &renderer->rays_buffer); // TODO ! [sleonard] -> переделать по-нормальному (wavefront)
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);

	err = clSetKernelArg(renderer->main_kernel, renderer->buffers_num + 1, /// +1 потому что еще есть int *img
			sizeof(cl_mem), &renderer->rays_buffer);
	rt_opencl_handle_error(ERR_OPENCL_SETARG, err);
}

void		rt_opencl_render(void *rt_ptr)
{
	const size_t	global_work_size[2] = {WIN_WIDTH, WIN_HEIGHT};
	int				err;
	t_rt_renderer	*renderer;
	t_rt			*rt;

	rt = rt_ptr;
	renderer = rt_get_renderer(rt->renderer_flags);
	rt_opencl_prepare_memory(rt, renderer); /// тут пока что setKernelArg и для img_gen кернела
	rt_opencl_setup_image_buffer(renderer);
	rt_setup_rays_gen_kernel(rt, renderer);
	rt_update_renderer_params(rt, renderer);
	if (rt->events.info)
		rt_print_debug_info(rt, renderer);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->img_gen_kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info(IMG_GEN_KERNEL_NAME);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->ray_gen_kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);
	if (rt->events.info)
		rt_print_opencl_profile_info(RAYS_GEN_KERNEL_NAME);

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->main_kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
	if (rt->events.info)
		rt_print_opencl_profile_info(MAIN_KERNEL_NAME);
	clReleaseEvent(g_opencl.profile_event);
	rt_opencl_handle_error(ERR_OPENCL_RUN_KERNELS, err);

	err |= clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);

//	err |= clEnqueueReadBuffer(g_opencl.queue, renderer->primary_img, CL_TRUE, 0,
//			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
//			g_img_data, 0, NULL, NULL);

	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);

	opencl_clean_memobjs(renderer);
}
