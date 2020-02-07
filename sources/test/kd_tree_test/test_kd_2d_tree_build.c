#include "test_header.h"
#include "test_kd_tree_header.h"

cl_float2	get_max_bound(cl_float2 *box_bounds)
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
//			if (g_test_kd_scene[i][j].bounds[0])
		}
	}
}

void		kd_get_bouds(cl_float2 *bounds)
{
//	bounds[0] =
//	bounds[1] =
//	bounds[2] =
//	bounds[3] =
}

void		build_kd_tree(t_kd_tree **tree, int level)
{
	if (!tree || level >= MAX_HEIGHT)
		return;
	t_kd_tree	*node;

	node = rt_safe_malloc(sizeof(t_kd_tree));
	kd_get_bouds(node->bounds);
	*tree = node;
	build_kd_tree(&(*tree)->left, level + 1);
	build_kd_tree(&(*tree)->right, level + 1);
}
