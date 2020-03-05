
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"
#include "color_utils.cl"

__kernel void		kernel_skybox_shade(
		__global __read_only const int *skybox_hit_pixel_indices,
		__global __read_only const t_ray *skybox_hit_rays_buffer,

		__global float3 *temp_float3_img_data,
		__global __write_only int *img_data // todo это для теста, потом убрать
)
{
	int		g_id = get_global_id(0);
	int		pixel_index = skybox_hit_pixel_indices[g_id];
	t_ray	ray = skybox_hit_rays_buffer[g_id];

	/// -> будет что-то подобное тому, что снизу
#ifdef RENDER_TEXTURES //todo тут тоже будет не =, а +=
	temp_float3_img_data[pixel_index] = ray.energy * skybox_color(&texture_info[SKYBOX_NUM], texture_list, skybox_normal(ray));
#else
	temp_float3_img_data[pixel_index] = ray.energy * get_float3_color(COL_BG);
#endif
//	img_data[pixel_index] = get_int_color(temp_float3_img_data[pixel_index]);
//	ray.energy = 0; // луч уже занулять не нужно? ведь он уже выведен из общего пайплайна
}
