#include "rt.h"

void		rt_unset_render_params(uint32_t *params, uint32_t target)
{
	*params &= ~target;
}

void		rt_set_render_params(uint32_t *params, uint32_t new_param)
{
	*params |= new_param;
}

void		rt_switch_render_param(uint32_t *params, uint32_t target)
{
	if (rt_params_isset(*params, target))
		rt_unset_render_params(params, target);
	else
		rt_set_render_params(params, target);
}

void		rt_set_render_algo(uint32_t *params, uint32_t new_algo)
{
	rt_unset_render_params(params, RENDER_RAYTRACE | RENDER_PATHTRACE | RENDER_RAYMARCH);
	rt_set_render_params(params, new_algo);
}
