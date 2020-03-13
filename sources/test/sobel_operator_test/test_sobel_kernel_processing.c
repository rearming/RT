#include "rt.h"
#include "rt_opencl.h"
#include "rt_wavefront_render.h"
#include <rt_debug.h>

void		test_sobel_processing(cl_kernel kernel, uint32_t find_intersection_work_size)
{
	int				err = CL_SUCCESS;
	t_ray			*rays_buffer = rt_safe_malloc(sizeof(t_ray) * find_intersection_work_size);
	int				*pixel_indices = rt_safe_malloc(sizeof(int) * find_intersection_work_size);

	err = clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_PRIMARY_RAYS_BUFFER].mem,
			CL_TRUE, 0, sizeof(t_ray) * find_intersection_work_size, rays_buffer, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);

	err |= clEnqueueReadBuffer(g_opencl.queue,
			g_opencl.wf_shared_buffers[RT_CL_MEM_PRIMARY_PIXEL_INDICES].mem,
			CL_TRUE, 0, sizeof(cl_int) * find_intersection_work_size, pixel_indices, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_READ_BUFFER, err);

	for (uint32_t i = 0; i < find_intersection_work_size; ++i)
	{
		if (rays_buffer[i].origin.x == -69.f)
			continue;
		rt_print_clfloat3(rays_buffer[i].origin, "origin");
		rt_print_clfloat3(rays_buffer[i].dir, "dir");
		rt_print_clfloat3(rays_buffer[i].energy, "energy");
	}

//	bzero(g_img_data, sizeof(cl_int) * WIN_WIDTH * WIN_HEIGHT);
//	for (uint32_t i = 0; i < find_intersection_work_size; ++i)
//	{
//		if (rays_buffer[i].energy.x > 0)
//			g_img_data[pixel_indices[i]] = COL_WHITE;
//	}

	free(rays_buffer);
	free(pixel_indices);
}
