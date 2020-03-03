
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

__kernel void		kernel_shade_skybox_or_nothing(
		__global __read_only const *
)
{
	// todo тут лучи которые никуда не попали будут заполнять массив

	/// -> будет что-то подобное тому, что снизу
#ifdef RENDER_TEXTURES
	result_color += ray.energy * skybox_color(&texture_info[SKYBOX_NUM], texture_list, skybox_normal(ray));
#else
	result_color += ray.energy * get_float3_color(COL_BG);
#endif
	ray.energy = 0;
}

