#include "rt.h"
#include "rt_opencl.h"
#include "rt_debug.h"
#include "time.h"


void 		kernel_generate_primary_rays()
{

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void 		kernel_generate_rays_aa_pathtrace()
{

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void 		kernel_generate_rays_aa_raytrace()
{

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void 		kernel_find_intersections()
{

	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void 		kernel_shade_and_generate_new_rays()
{
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void 		kernel_fill_img_mix_colors()
{
	err = clEnqueueNDRangeKernel(g_opencl.queue,
			renderer->kernel, 2, NULL, global_work_size, NULL, 0, NULL, &g_opencl.profile_event);
}

void 		wavefront(void *rt_ptr)
{
	cl_program	generate_primary_rays_program;
	cl_kernel	generate_primary_rays_kernel;

	kernel_generate_primary_rays(); // OUT_BUFFERS -> 1) rays_buffer 2) pixel_indices 3) buffers_len

	kernel_find_intersections(); // IN_BUFFERS <- rays_buffer | OUT_BUFFERS -> 1) obj_indices 2) ray_hits (normal, position) 3) pixel_indices 4) buffer_len
	kernel_shade_and_generate_new_rays(); // IN_BUFFERS <- 1) obj_indices 2) ray_hits (normal, position) 3) pixel_indices 4) buffer_len | OUT_BUFFERS -> rays_buffer

	kernel_fill_img_mix_colors(); // IN_BUFFERS <- 1) struct {float3 color, int pixel_index} | OUT_BUFFERS -> int *pixels


}