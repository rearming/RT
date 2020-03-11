#include "rt.h"

//todo парсинг (и валидация) параметров рендеринга из json'a [gfoote]
static inline void		rt_init_pathtrace_params(t_pathtrace_params *out_pathtrace_params)
{
	out_pathtrace_params->current_samples_num = 1;
	out_pathtrace_params->max_depth = 8;
}

static inline void		rt_init_raytrace_params(t_raytrace_params *out_raytrace_params)
{
	out_raytrace_params->max_depth = 8;
}

void					rt_init_renderer_params(t_renderer_params *out_opencl_params)
{
	out_opencl_params->seed = drand48();
	out_opencl_params->gamma = 2.2f;
	out_opencl_params->exposure = 1;
	rt_init_pathtrace_params(&out_opencl_params->pathtrace_params);
	rt_init_raytrace_params(&out_opencl_params->raytrace_params);
}