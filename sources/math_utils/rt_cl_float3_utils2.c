/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_float3_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_math_utils.h"

cl_float3	mul_float3(cl_float3 vec, float mul)
{
	cl_float3	result;

	result.x = vec.x * mul;
	result.y = vec.y * mul;
	result.z = vec.z * mul;
	return (result);
}

cl_float3	saturate_float3(cl_float3 value)
{
	return ((cl_float3){{
		rt_saturatef(value.x),
		rt_saturatef(value.y),
		rt_saturatef(value.z)}});
}
