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

void		build_kd_tree_recursive(t_kd_tree *tree,
									t_aabb *all_aabbs,
									int level,
									int *index)
{
	init_node(tree);
	if (level >= KD_TREE_MAX_HEIGHT)
		return;

	t_aabb	left_aabb;
	t_aabb	right_aabb;

	t_aabb_objects	left_objects;
	t_aabb_objects	right_objects;

	float			split;
	int				split_axis;

	float	sah = kd_split_buckets_sah(tree->aabb, &tree->objects,
			all_aabbs, &left_aabb, &right_aabb, &left_objects, &right_objects,
			&split, &split_axis);
	if (sah > tree->sah)
	{
		free(left_objects.indices);
		free(right_objects.indices);
		return;
	}

	tree->split = split;
	tree->split_axis = split_axis;
	tree->objects.num = NOT_SET;
	free(tree->objects.indices);
	tree->left_index = ++(*index);
	tree->right_index = ++(*index);

	tree->left = rt_safe_malloc(sizeof(t_kd_tree));
	tree->left->objects = left_objects;
	tree->left->aabb = left_aabb;
	tree->left->sah = kd_get_aabb_area(left_aabb) * (float)left_objects.num;
	build_kd_tree_recursive(tree->left, all_aabbs, level + 1, index);

	tree->right = rt_safe_malloc(sizeof(t_kd_tree));
	tree->right->objects = right_objects;
	tree->right->aabb = right_aabb;
	tree->right->sah = kd_get_aabb_area(right_aabb) * (float)right_objects.num;
	build_kd_tree_recursive(tree->right, all_aabbs, level + 1, index);
}