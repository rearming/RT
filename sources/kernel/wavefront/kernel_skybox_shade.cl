
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
