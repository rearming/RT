#include "rt.h"
#include "rt_wavefront_render.h"

enum e_cl_mem_types		switch_ray_buffers(int iteration)
{
	return iteration % 2 == 0 ? RT_CL_MEM_RAYS_BUFFER : RT_CL_MEM_OUT_RAYS_BUFFER;
}
