
__kernel void		kernel_material_shade_generate_new_rays(
		__global __read_only const int *pixel_material_indices,
		__global __write_only t_ray *out_rays_buffer,
		__global __write_only int *out_rays_pixel_indices,
		__global __write_only int *out_rays_buffer_len,
		// offset для записи новых лучей в texture_shade
)
{
	t_ray new_ray;

//	t_material	material =
//#ifdef RENDER_RAYTRACE
//	shade_raytrace();
//#endif
//#ifdef RENDER_PATHTRACE
//	shade_pathtrace();
//#endif
	/// если генерируем новый луч ->
	out_rays_pixel_indices[out_rays_buffer_len] = pixel_material_indices[g_id];
	out_rays_buffer[out_rays_buffer_len] = new_ray;
	atomic_inc(out_rays_buffer_len);
}
