#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
#include "prototypes.cl"

#include "utils.cl"

__kernel void	kernel_generate_primary_rays(
		__global __read_only const t_camera *camera,
		__global __write_only t_ray *out_rays_buffer)
{
	int3		img_point = (int3)(get_global_id(0), get_global_id(1), 0);
	int			g_id = img_point.x + img_point.y * WIN_WIDTH;

	out_rays_buffer[g_id] = get_ray(convert_float3(img_point), &scene->camera);
}
