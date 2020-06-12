/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				get_int_color(cl_float3 float3_color)
{
	t_color		color;

	color.rgb.a = 0;
	color.rgb.r = float3_color.x * 255;
	color.rgb.g = float3_color.y * 255;
	color.rgb.b = float3_color.z * 255;
	return (color.value);
}

cl_float3		get_float3_color(int hex_color)
{
	const t_color		color = {hex_color};

	return ((cl_float3){{
		(float)color.rgb.r / 255,
		(float)color.rgb.g / 255,
		(float)color.rgb.b / 255}});
}

cl_float		float3_color_power(cl_float3 color)
{
	return (color.x > 0 || color.y > 0 || color.z > 0
	? ((color.x + color.y + color.z) / 3) : 0);
}
