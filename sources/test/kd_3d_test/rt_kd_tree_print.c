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
	ft_printf("aabb:\n");
	print_aabb(node->aabb);
	ft_printf("sah: [%.3f]\n", node->sah);
	if (node->indices[0] != NOT_SET)
	{
		ft_printf("obj indices:\n");
		for (int i = 0; i < MAX_OBJ_IN_LEAF; ++i)
			ft_printf("[%i] ", node->indices[i]);
	}
	ft_printf("\n\n");
}

void	print_kd_tree_recursive(t_kd_tree *tree, int level)
{
	if (!tree)
		return;
	ft_printf("k-d node:\n");
	ft_printf("level: [%i]\n", level);
	print_kd_node(tree);
	g_nodes_num++;
	print_kd_tree_recursive(tree->left, level + 1);
	print_kd_tree_recursive(tree->right, level + 1);
}

void	print_kd_tree(t_kd_tree *tree)
{
	print_kd_tree_recursive(tree, 0);
	ft_printf("nodes number: [%i]\n", g_nodes_num);
}


