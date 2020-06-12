/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_split_buckets_sah.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_kd_tree.h"
#include "rt_kd_tree_build.h"

static inline t_split	kd_split(t_aabb root_aabb, int axis, int split_num)
{
	t_split		split;

	split.s.min = root_aabb.min;
	split.s.min.s[axis] = root_aabb.min.s[axis]
			+ ((root_aabb.max.s[axis] - root_aabb.min.s[axis]) / BUCKETS)
			* (float)split_num;
	split.s.max = root_aabb.max;
	split.s.max.s[axis] = split.s.min.s[axis];
	return (split);
}

/*
** @param fn stands for fuck_norme
** @param op - old_params
** split.s.min.s[axis] == split.s.max.s[axis]
*/

static inline void		update_params(
		t_kd_split_params *op,
		t_split_internal_params *fn)
{
	float	sah;

	sah = EMPTY_COST
			+ (float)fn->left_objects.num * kd_get_aabb_area(fn->left_aabb)
			+ (float)fn->right_objects.num * kd_get_aabb_area(fn->right_aabb);
	if (sah < fn->best_sah)
	{
		if (fn->best_sah != INFINITY)
		{
			free(op->out_left_objects.indices);
			free(op->out_right_objects.indices);
		}
		fn->best_sah = sah;
		op->out_left_aabb = fn->left_aabb;
		op->out_right_aabb = fn->right_aabb;
		op->out_left_objects = fn->left_objects;
		op->out_right_objects = fn->right_objects;
		op->out_split = fn->split.s.min.s[fn->axis];
		op->out_split_axis = fn->axis;
	}
	else
	{
		free(fn->left_objects.indices);
		free(fn->right_objects.indices);
	}
}

static inline void		split(
		t_kd_split_params *params,
		t_split_internal_params *fn)
{
	fn->split = kd_split(params->root_aabb, fn->axis, fn->split_num);
	fn->left_aabb = params->root_aabb;
	fn->right_aabb = params->root_aabb;
	fn->left_aabb.max = fn->split.s.max;
	fn->right_aabb.min = fn->split.s.min;
	fn->left_objects = kd_get_objects_in_aabb(
			fn->left_aabb, params->all_aabbs, params->root_objects);
	fn->right_objects = kd_get_objects_in_aabb(
			fn->right_aabb, params->all_aabbs, params->root_objects);
	update_params(params, fn);
	fn->split_num++;
}

float					kd_split_buckets_sah(t_kd_split_params *params)
{
	t_split_internal_params		fn;

	fn.axis = 0;
	fn.best_sah = INFINITY;
	while (fn.axis < AXIS_NUM)
	{
		fn.split_num = 1;
		while (fn.split_num < BUCKETS)
			split(params, &fn);
		fn.axis++;
	}
	return (fn.best_sah);
}
