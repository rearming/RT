#include "rt.h"
#include "rt_kd_tree.h"

int		kd_tree_count_nodes(t_kd_tree *tree)
{
	if (!tree)
		return 0;
	return kd_tree_count_nodes(tree->left) + kd_tree_count_nodes(tree->right) + 1;
}
