#include "rt.h"

void		rt_opencl_prepare_memory(t_rt *rt)
{
	g_opencl.opencl_memobj_number = 3;
	rt_opencl_copy_host_mem_to_kernel(g_opencl.opencl_memobj_number,
		(t_opencl_mem_obj){&rt->scene,
			sizeof(t_scene), RT_DEFAULT_MEM_FLAG},
		(t_opencl_mem_obj){rt->scene.objects,
			sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG},
		(t_opencl_mem_obj){rt->scene.lights,
			sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG}
			);
}

void		rt_opencl_render(t_rt *rt)
{
	const size_t	kernel_num = OPENCL_KERNEL_NUM;
	int				err;

	rt_opencl_prepare_memory(rt);
	rt_opencl_setup_image_buffer();
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			g_opencl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, NULL);
	if (err)
		rt_raise_error(ERR_OPENCL_RUN_KERNELS);
	err = clEnqueueReadBuffer(g_opencl.queue, g_opencl.img_data_mem, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			g_img_data, 0, NULL, NULL);
	if (err)
		rt_raise_error(ERR_OPENCL_READ_BUFFER);
	opencl_clean_memobjs();
}
