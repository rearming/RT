/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_float3_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_math_utils.h"

cl_float3	fmin_float3(cl_float3 a, cl_float3 b)
{
	return ((cl_float3){{fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z)}});
}

cl_float3	fmax_float3(cl_float3 a, cl_float3 b)
{
	return ((cl_float3){{fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z)}});
}

cl_float2	fmin_float2(cl_float2 a, cl_float2 b)
{
	return ((cl_float2){{fminf(a.x, b.x), fminf(a.y, b.y)}});
}

cl_float2	fmax_float2(cl_float2 a, cl_float2 b)
{
	return ((cl_float2){{fmaxf(a.x, b.x), fmaxf(a.y, b.y)}});
}

bool		rt_float3_equals(cl_float3 a, cl_float3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
