#include <time.h>
#include "../test_header.h"
#include "kd_2d_tree_header.h"

#ifdef __APPLE__
# define scene_random arc4random
#else
# define scene_random rand
#endif

void	print_cl_float2(cl_float2 vec, const char *definition)
{
	ft_printf("%s:  x: [%.2f], y: [%.2f]\n", definition, vec.x, vec.y);
}

void	print_2d_aabb(t_aabb aabb)
{
	print_cl_float2(aabb.bounds.min, "min");
	print_cl_float2(aabb.bounds.max, "max");
}

void	print_all_2d_aabbs(t_aabb *aabbs, int num_aabb)
{
	for (int i = 0; i < num_aabb; ++i)
		print_2d_aabb(aabbs[i]);
}

void	kd_2d_print_node(t_kd_tree *node)
{
	ft_printf("obj num: [%i]\n", node->obj_num);
	ft_printf("sah: [%i]\n", node->sah);
	print_2d_aabb(node->aabb);
	if (node->indices[0] != NOT_SET)
	{
		ft_printf("obj indices:\n");
		for (int j = 0; j < MAX_OBJ_IN_LEAF; ++j)
			ft_printf("[%i] ", node->indices[j]);
	}
	ft_printf("\n\n");
}

int		g_2d_nodes_num = 0;

void 	print_2d_kd_traverse(t_kd_tree *root, int level)
{
	if (!root)
		return;
	ft_printf("node's level: [%i]\n", level);
//	ft_printf("nodes num now: [%i]\n", g_2d_nodes_num);
	kd_2d_print_node(root);
	g_2d_nodes_num++;
	print_2d_kd_traverse(root->left, level + 1);
	print_2d_kd_traverse(root->right, level + 1);
}

void	print_2d_kd_tree(t_kd_tree *root)
{
	g_2d_nodes_num = 0;
	print_2d_kd_traverse(root, 0);
	ft_printf("nodes number: [%i]\n", g_2d_nodes_num);
	ft_printf("max height: [%i]\n", g_max_height);
}


