#include "rt.h"
#include "rt_wavefront_render.h"

enum e_cl_mem_types		switch_ray_buffers(int iteration)
{
	return iteration % 2 == 0 ? RT_CL_MEM_RAYS_BUFFER : RT_CL_MEM_OUT_RAYS_BUFFER;
}

void					wavefront_release_buffers(bool release_all)
{
	for (int i = 0; i < 37; ++i) // ты че даун это хардкодить?
	{
		if (g_opencl.wavefront_shared_buffers[i].copy_mem == true || release_all)
			clReleaseMemObject(g_opencl.wavefront_shared_buffers[i].mem);
	}
	if (release_all)
		free(g_opencl.wavefront_shared_buffers);
}
