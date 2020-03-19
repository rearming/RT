#include "rt.h"
#include "rt_kd_tree.h"

void	free_kd_tree(t_kd_tree *tree, bool free_indices)
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

char	*rt_get_kd_binary_path(const char *obj_path)
{
	char		*binary_path;
	char		*tmp;
	size_t		size = ft_strlen_char(obj_path, '.') + 1;

	tmp = rt_safe_malloc(size + 1);
	ft_memcpy(tmp, obj_path, size);
	tmp[size] = 0;
	ft_sprintf(&binary_path, "%s%s", tmp, KD_TREE_BINARY_EXT);
	free(tmp);
	return (binary_path);
}
