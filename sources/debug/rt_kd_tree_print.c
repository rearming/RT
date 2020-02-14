#include "rt.h"
#include "rt_debug.h"
#include "rt_kd_tree.h"

int 	g_nodes_num = 0;

void	print_aabb(t_aabb aabb)
{
	rt_print_clfloat3(aabb.bounds.min, "min");
	rt_print_clfloat3(aabb.bounds.max, "max");
}

void	print_all_aabbs(t_aabb *aabbs, int num_aabb)
{
	for (int i = 0; i < num_aabb; ++i)
		print_aabb(aabbs[i]);
}

void	print_kd_node(t_kd_tree *node)
{
	printf("aabb:\n");
	print_aabb(node->aabb);
	printf("sah: [%.3f]\n", node->sah);
	printf("obj num: [%i]\n", node->objects.num);
	printf("left index: [%i]\n", node->left_index);
	printf("right index: [%i]\n", node->right_index);

#ifdef PRINT_INDICES
	if (node->objects.num > 0)
	{
		printf("obj indices:\n");
		for (int i = 0; i < node->objects.num; ++i)
			printf("[%i] ", node->objects.indices[i]);
	}
#endif
	printf("\n\n");
}

void	print_kd_arr_node(t_kd_arr_node *node)
{
	printf("aabb:\n");
	print_aabb(node->aabb);
	printf("sah: [%.3f]\n", node->sah);
	printf("obj num: [%i]\n", node->objects.num);
	printf("left index: [%i]\n", node->left_index);
	printf("right index: [%i]\n", node->right_index);

#ifdef PRINT_INDICES
	if (node->objects.num > 0)
	{
		printf("obj indices:\n");
		for (int i = 0; i < node->objects.num; ++i)
			printf("[%i] ", node->objects.indices[i]);
	}
#endif
	printf("\n\n");
}

void	print_kd_tree_recursive(t_kd_tree *tree, int level)
{
	if (!tree)
		return;
	printf("k-d node:\n");
//	printf("level: [%i]\n", level);
	print_kd_node(tree);
	g_nodes_num++;
	print_kd_tree_recursive(tree->left, level + 1);
	print_kd_tree_recursive(tree->right, level + 1);
}

void	print_kd_tree_arr(t_kd_arr_node *tree_arr, int index)
{
	if (index == NOT_SET)
		return;
	printf("k-d node:\n");
//	printf("index: [%i]\n", index);
	print_kd_arr_node(&tree_arr[index]);
	print_kd_tree_arr(tree_arr, tree_arr[index].left_index);
	print_kd_tree_arr(tree_arr, tree_arr[index].right_index);
}

void	print_kd_tree(t_kd_tree *tree)
{
	print_kd_tree_recursive(tree, 0);
	printf("nodes number: [%i]\n", g_nodes_num);
	g_nodes_num = 0;
}


