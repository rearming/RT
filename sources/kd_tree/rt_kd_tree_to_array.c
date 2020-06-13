/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_kd_tree_to_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by sleonard          #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_kd_tree.h"

t_kd_arr_tree	get_arr_node(t_kd_tree *node)
{
	t_kd_arr_tree	arr_node;

	arr_node.aabb = node->aabb;
	arr_node.split_axis = node->split_axis;
	arr_node.sah = node->sah;
	arr_node.split = node->split;
	arr_node.objects = node->objects;
	arr_node.right_index = node->right_index;
	arr_node.left_index = node->left_index;
	return (arr_node);
}

void			kd_tree_to_array_recursive(t_kd_tree *tree,
								t_kd_arr_tree *out_arr,
								int *out_obj_indices_num)
{
	if (tree->left)
	{
		out_arr[tree->left_index] = get_arr_node(tree->left);
		if (out_arr[tree->left_index].objects.num != NOT_SET)
			(*out_obj_indices_num) += out_arr[tree->left_index].objects.num;
		kd_tree_to_array_recursive(tree->left, out_arr, out_obj_indices_num);
	}
	if (tree->right)
	{
		out_arr[tree->right_index] = get_arr_node(tree->right);
		if (out_arr[tree->right_index].objects.num != NOT_SET)
			(*out_obj_indices_num) += out_arr[tree->right_index].objects.num;
		kd_tree_to_array_recursive(tree->right, out_arr, out_obj_indices_num);
	}
}

t_kd_arr_tree	*kd_tree_to_array(
		t_kd_tree *tree,
		int *out_nodes_num,
		int *out_obj_indices_num)
{
	int				nodes_num;
	t_kd_arr_tree	*kd_tree_arr;

	nodes_num = kd_tree_count_nodes(tree);
	kd_tree_arr = rt_safe_malloc(sizeof(t_kd_tree) * nodes_num);
	kd_tree_arr[0] = get_arr_node(&tree[0]);
	kd_tree_to_array_recursive(tree, kd_tree_arr, out_obj_indices_num);
	*out_nodes_num = nodes_num;
	return (kd_tree_arr);
}
