
__kernel void		kernel_texture_shade_generate_new_rays(
		__global __read_only const *hit_obj_indices,
		__global __read_only const int *material_buffers_len,
		__global __write_only t_ray *out_rays_buffer,
		__global __read_only int *out_rays_buffer_len,
)
{
	t_ray new_ray;

	out_rays_buffer[g_id + *material_buffers_len] = new_ray;// offset для записи новых лучей
}
