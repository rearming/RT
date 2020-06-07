#include "rt.h"

static inline void		rt_init_pathtrace_params(
		t_pathtrace_params *out_pathtrace_params,
		t_cl_info clInfo)
{
	out_pathtrace_params->current_samples_num = 0;
	out_pathtrace_params->max_depth = clInfo.max_depth_pathtrace;
}

static inline void		rt_init_raytrace_params(
		t_raytrace_params *out_raytrace_params,
		t_cl_info clInfo)
{
	out_raytrace_params->max_depth = clInfo.max_depth_raytrace;
}

void					rt_init_render_params(
		t_render_params *out_opencl_params,
		t_cl_info clInfo)
{
	out_opencl_params->seed = drand48();
	out_opencl_params->gamma = clInfo.gamma;
	out_opencl_params->exposure = clInfo.exposure;
	rt_init_pathtrace_params(&out_opencl_params->pathtrace_params, clInfo);
	rt_init_raytrace_params(&out_opencl_params->raytrace_params, clInfo);
}
