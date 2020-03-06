
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"

__kernel void		kernel_texture_shade(
		__global __read_only const int *hit_obj_indices,
		__global __read_only const int *material_buffers_len,
		__global __write_only t_ray *out_rays_buffer,
		__global __read_only int *out_rays_buffer_len
)
{
//	t_ray new_ray;

//	out_rays_buffer[g_id + *material_buffers_len] = new_ray;// offset для записи новых лучей
}
