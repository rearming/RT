/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_tree_build.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by gfoote            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_KD_TREE_BUILD_H
# define RT_KD_TREE_BUILD_H

typedef struct	s_kd_split_buckets_params
{
	t_aabb			root_aabb;
	t_aabb_objects	*root_objects;
	t_aabb			*all_aabbs;
	t_aabb			out_left_aabb;
	t_aabb			out_right_aabb;
	t_aabb_objects	out_left_objects;
	t_aabb_objects	out_right_objects;
	float			out_split;
	int				out_split_axis;
}				t_kd_split_params;

typedef struct	s_split_internal_params
{
	float			best_sah;
	int				axis;
	int				split_num;
	t_aabb_objects	left_objects;
	t_aabb_objects	right_objects;
	t_split			split;
	t_aabb			left_aabb;
	t_aabb			right_aabb;
}				t_split_internal_params;

void			build_kd_tree_recursive(
		t_kd_tree *tree,
		t_aabb *all_aabbs,
		int level,
		int *index);
float			kd_split_buckets_sah(t_kd_split_params *params);

#endif
