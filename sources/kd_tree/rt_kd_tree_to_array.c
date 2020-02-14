#include "rt.h"
#include "rt_kd_tree.h"

t_kd_arr_node	get_arr_node(t_kd_tree *node)
{
	t_kd_arr_node	arr_node;

	arr_node.aabb = node->aabb;
	arr_node.split_axis = node->split_axis;
	arr_node.sah = node->sah;
	arr_node.split = node->split;
	arr_node.objects = node->objects;
	arr_node.right_index = node->right_index;
	arr_node.left_index = node->left_index;
	return (arr_node);
}

void 			kd_tree_to_array_recursive(t_kd_tree *tree, t_kd_arr_node *out_arr)
{
	if (tree->left)
	{
		out_arr[tree->left_index] = get_arr_node(tree->left);
		kd_tree_to_array_recursive(tree->left, out_arr);
	}
	if (tree->right)
	{
		out_arr[tree->right_index] = get_arr_node(tree->right);
		kd_tree_to_array_recursive(tree->right, out_arr);
	}
}

t_kd_arr_node	*kd_tree_to_array(t_kd_tree *tree)
{
	int				nodes_num;
	t_kd_arr_node	*kd_tree_arr;

	nodes_num = kd_tree_count_nodes(tree);
	kd_tree_arr = rt_safe_malloc(sizeof(t_kd_tree) * nodes_num);
	kd_tree_arr[0] = get_arr_node(&tree[0]);
	kd_tree_to_array_recursive(tree, kd_tree_arr);
	return (kd_tree_arr);
}

