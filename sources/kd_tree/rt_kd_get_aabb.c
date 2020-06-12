/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_get_aabb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_math_utils.h"
#include "rt_kd_tree.h"

t_aabb		get_aabb_polygon(cl_float3 vertices[RT_DEFAULT_POLYGON_VERTICES])
{
	t_aabb	aabb;

	aabb.min = rt_float3_sub(
			fmin_float3(vertices[0], fmin_float3(vertices[1], vertices[2])),
			(cl_float3) {{
				AABB_OFFSET_EPSILON, AABB_OFFSET_EPSILON, AABB_OFFSET_EPSILON
			}});
	aabb.max = rt_float3_add(
			fmax_float3(vertices[0], fmax_float3(vertices[1], vertices[2])),
			(cl_float3){{
				AABB_OFFSET_EPSILON, AABB_OFFSET_EPSILON, AABB_OFFSET_EPSILON
			}});
	return (aabb);
}

t_aabb		get_root_aabb(t_aabb *aabbs, int num_aabbs)
{
	t_aabb	root_aabb;
	int		i;

	i = 0;
	root_aabb.min = (cl_float3){{INFINITY, INFINITY, INFINITY}};
	root_aabb.max = (cl_float3){{-INFINITY, -INFINITY, -INFINITY}};
	while (i < num_aabbs)
	{
		root_aabb.min = fmin_float3(root_aabb.min, aabbs[i].min);
		root_aabb.max = fmax_float3(root_aabb.max, aabbs[i].max);
		i++;
	}
	return (root_aabb);
}

t_aabb		*rt_get_all_aabbs(t_meshes *meshes)
{
	t_aabb		*tris_aabb;
	int			i;

	tris_aabb = rt_safe_malloc(sizeof(t_aabb) * meshes->num_polygons);
	i = 0;
	while (i < meshes->num_polygons)
	{
		tris_aabb[i] = get_aabb_polygon(
				(cl_float3[RT_DEFAULT_POLYGON_VERTICES]){
					meshes->vertices[meshes->polygons[i].vert_i[0]],
					meshes->vertices[meshes->polygons[i].vert_i[1]],
					meshes->vertices[meshes->polygons[i].vert_i[2]]});
		i++;
	}
	return (tris_aabb);
}
