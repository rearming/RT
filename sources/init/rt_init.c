#include "rt.h"

//todo парсинг (и валидация) параметров рендеринга из json'a ?
void		rt_init_pathtrace_params(t_pathtrace_params *out_pathtrace_params)
{
	out_pathtrace_params->current_samples_num = 0;
	out_pathtrace_params->max_depth = 8;
}

void		rt_init_raytrace_params(t_raytrace_params *out_raytrace_params)
{
	out_raytrace_params->max_depth = 8;
}

void		rt_init_opencl_params(t_opencl_params *out_opencl_params)
{
//	out_opencl_params->render_algo = RAY_TRACE;
	out_opencl_params->render_algo = PATH_TRACE;
	out_opencl_params->seed = drand48();
	rt_init_pathtrace_params(&out_opencl_params->pathtrace_params);
	rt_init_raytrace_params(&out_opencl_params->raytrace_params);
}

void		rt_init_events(t_events *events)
{
	events->w = false;
	events->a = false;
	events->s = false;
	events->d = false;
	events->info = false;
	events->space = false;
	events->lshift = false;
}

void		rt_init(t_rt *out_rt, const char *json_scene_file)
{
	//rt_sdl_init();
	//rt_opencl_init();
	out_rt->scene = rt_parse_scene(json_scene_file);
	//rt_init_opencl_params(&out_rt->opencl_params);
	//rt_init_events(&out_rt->events);
}
