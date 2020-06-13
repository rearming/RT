/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_debug_print_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_debug.h"

void		rt_print_clfloat3(cl_float3 vec, const char *definition)
{
	printf("%s: x: [%f], y: [%f], z: [%f]\n", definition, vec.x, vec.y, vec.z);
}

void		rt_print_float3_color(cl_float3 color, const char *definition)
{
	printf("%s: r: [%.2f], g: [%.2f], arr: [%.2f]\n",
			definition, color.x, color.y, color.z);
}
