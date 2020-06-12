/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_settings_change.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rt_unset_bit(uint32_t *bitfield, uint32_t target)
{
	*bitfield &= ~target;
}

void		rt_set_bit(uint32_t *bitfield, uint32_t new_param)
{
	*bitfield |= new_param;
}

void		rt_switch_bit(uint32_t *bitfield, uint32_t target)
{
	if (rt_bit_isset(*bitfield, target))
		rt_unset_bit(bitfield, target);
	else
		rt_set_bit(bitfield, target);
}

void		rt_set_render_algo(uint32_t *params, uint32_t new_algo)
{
	rt_unset_bit(params, RENDER_RAYTRACE | RENDER_PATHTRACE | RENDER_RAYMARCH);
	rt_set_bit(params, new_algo);
}
