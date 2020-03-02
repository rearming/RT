#include "rt.h"
#include "rt_kd_tree.h"

void free_kd_tree(t_kd_tree *tree, bool free_indices)
{
	if (!tree)
		return;
	free_kd_tree(tree->left, free_indices);
	free_kd_tree(tree->right, free_indices);
	if (tree->objects.num != NOT_SET && free_indices)
		free(tree->objects.indices);
	free(tree);
}

int		kd_tree_count_nodes(t_kd_tree *tree)
{
	if (!tree)
		return 0;
	return kd_tree_count_nodes(tree->left) + kd_tree_count_nodes(tree->right) + 1;
}
