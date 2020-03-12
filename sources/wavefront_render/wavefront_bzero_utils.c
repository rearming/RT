#include "rt.h"
#include "rt_opencl.h"
#include "rt_wavefront_render.h"

void		bzero_buffer(enum e_cl_mem_types mem_index)
{
	int			err = CL_SUCCESS;
	cl_uint		zero = 0;

	printf("bzero buffer\n");
	err |= clEnqueueWriteBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[mem_index].mem,
			CL_TRUE, 0, sizeof(cl_uint), &zero, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_FILL_BUFFER, err);
}

void		bzero_float3_temp_img(cl_float3 *zero_arr)
{
	int			err = CL_SUCCESS;

	err |= clEnqueueWriteBuffer(g_opencl.queue, g_opencl.wavefront_shared_buffers[RT_CL_MEM_TEMP_FLOAT3_IMG_DATA].mem,
			CL_TRUE, 0, sizeof(cl_float3) * WIN_WIDTH * WIN_HEIGHT, zero_arr, 0, NULL, NULL);
	rt_opencl_handle_error(ERR_OPENCL_FILL_BUFFER, err);
}