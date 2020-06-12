/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_build_recursive.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_kd_tree.h"
#include "rt_kd_tree_build.h"

static void	init_node(t_kd_tree *tree)
{
	tree->left = NULL;
	tree->right = NULL;
	tree->split = NOT_SET;
	tree->split_axis = NOT_SET;
	tree->left_index = NOT_SET;
	tree->right_index = NOT_SET;
}

static void	fill_local_root_node(
		t_kd_tree *tree,
		t_kd_split_params *split_params,
		int *index)
{
	tree->split = split_params->out_split;
	tree->split_axis = split_params->out_split_axis;
	tree->objects.num = NOT_SET;
	free(tree->objects.indices);
	tree->left_index = ++(*index);
	tree->right_index = ++(*index);
}

static void	fill_local_leaf_node(
		t_kd_tree **tree,
		t_aabb_objects objects,
		t_aabb aabb)
{
	(*tree) = rt_safe_malloc(sizeof(t_kd_tree));
	(*tree)->objects = objects;
	(*tree)->aabb = aabb;
	(*tree)->sah = kd_get_aabb_area(aabb) * (float)objects.num;
}

void		build_kd_tree_recursive(
		t_kd_tree *tree,
		t_aabb *all_aabbs,
		int level,
		int *index)
{
	t_kd_split_params	split_params;

	init_node(tree);
	if (level >= KD_TREE_MAX_HEIGHT)
		return ;
	split_params.root_aabb = tree->aabb;
	split_params.root_objects = &tree->objects;
	split_params.all_aabbs = all_aabbs;
	if (kd_split_buckets_sah(&split_params) > tree->sah)
	{
		free(split_params.out_left_objects.indices);
		free(split_params.out_right_objects.indices);
		return ;
	}
	fill_local_root_node(tree, &split_params, index);
	fill_local_leaf_node(&tree->left, split_params.out_left_objects,
			split_params.out_left_aabb);
	build_kd_tree_recursive(tree->left, all_aabbs, level + 1, index);
	fill_local_leaf_node(&tree->right, split_params.out_right_objects,
			split_params.out_right_aabb);
	build_kd_tree_recursive(tree->right, all_aabbs, level + 1, index);
}
