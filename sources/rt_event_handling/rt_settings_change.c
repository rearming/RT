#include "rt.h"

void		rt_unset_bit(uint32_t *params, uint32_t target)
{
	*params &= ~target;
}

void		rt_set_bit(uint32_t *params, uint32_t new_param)
{
	*params |= new_param;
}

void		rt_switch_bit(uint32_t *params, uint32_t target)
{
	if (rt_bit_isset(*params, target))
		rt_unset_bit(params, target);
	else
		rt_set_bit(params, target);
}

void		rt_set_render_algo(uint32_t *params, uint32_t new_algo)
{
	rt_unset_bit(params, RENDER_RAYTRACE | RENDER_PATHTRACE | RENDER_RAYMARCH);
	rt_set_bit(params, new_algo);
}
