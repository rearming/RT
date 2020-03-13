#include "rt.h"
#include "rt_wavefront_render.h"

t_cl_mem_types	switch_ray_buffers(int iteration)
{
	return iteration % 2 == 0 ? RT_CL_MEM_RAYS_BUFFER : RT_CL_MEM_OUT_RAYS_BUFFER;
}

void			wavefront_release_buffers(uint32_t current_render_state)
{
	for (int i = 0; i < g_opencl.wf_shared_buffers_len; ++i)
	{
		if (g_opencl.wf_shared_buffers[i].realloc_state & current_render_state || current_render_state & STATE_EXIT)
			clReleaseMemObject(g_opencl.wf_shared_buffers[i].mem);
	}
	if (current_render_state & STATE_EXIT)
		free(g_opencl.wf_shared_buffers);
}
