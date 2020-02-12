#include "rt.h"
#include "rt_kd_tree.h"

t_split		kd_split(t_aabb root_aabb, int axis, int split_num)
{
	t_split		split;

	split.s.min = root_aabb.bounds.min;
	split.s.min.s[axis] = root_aabb.bounds.min.s[axis] + ((root_aabb.bounds.max.s[axis] - root_aabb.bounds.min.s[axis]) / BUCKETS) * (float)split_num;
	split.s.max = root_aabb.bounds.max;
	split.s.max.s[axis] = split.s.min.s[axis];
	return (split);
}

bool		kd_is_obj_in_aabb(t_aabb root_aabb, t_aabb obj_aabb)
{
	if ((obj_aabb.bounds.min.x <= root_aabb.bounds.max.x
	&& obj_aabb.bounds.min.y <= root_aabb.bounds.max.y
	&& obj_aabb.bounds.min.z <= root_aabb.bounds.max.z
	&& obj_aabb.bounds.max.x >= root_aabb.bounds.min.x
	&& obj_aabb.bounds.max.y >= root_aabb.bounds.min.y
	&& obj_aabb.bounds.max.z >= root_aabb.bounds.min.z)
	||
	(obj_aabb.bounds.max.x >= root_aabb.bounds.min.x
	&& obj_aabb.bounds.max.y >= root_aabb.bounds.min.y
	&& obj_aabb.bounds.max.z >= root_aabb.bounds.min.z
	&& obj_aabb.bounds.min.x <= root_aabb.bounds.max.x
	&& obj_aabb.bounds.min.y <= root_aabb.bounds.max.y
	&& obj_aabb.bounds.min.z <= root_aabb.bounds.max.z))
		return true;
	return false;
}

t_aabb_objects		kd_get_objects_in_aabb(t_aabb aabb, t_aabb *all_aabbs, t_aabb_objects *prev_objects)
{
	t_aabb_objects	aabb_objects;
	int				i;

	aabb_objects.num = 0;
	aabb_objects.indices = rt_safe_malloc(sizeof(int) * prev_objects->num);
	i = 0;
	while (i < prev_objects->num)
	{
		if (kd_is_obj_in_aabb(aabb, all_aabbs[prev_objects->indices[i]]))
		{
			aabb_objects.indices[aabb_objects.num] = prev_objects->indices[i];
			aabb_objects.num++;
		}
		i++;
	}
	return aabb_objects;
}

float		kd_get_aabb_area(t_aabb aabb)
{
	return ((aabb.bounds.max.x - aabb.bounds.min.x)
	* (aabb.bounds.max.y - aabb.bounds.min.y)
	* (aabb.bounds.max.z - aabb.bounds.min.z));
}

float		kd_split_buckets_sah(t_aabb root_aabb,
						   t_aabb_objects *root_objects,
						   t_aabb *all_aabbs,
						   t_aabb *out_left_aabb,
						   t_aabb *out_right_aabb,
						   t_aabb_objects *out_left_objects,
						   t_aabb_objects *out_right_objects)
{
	float			best_sah;
	int				axis;
	int				split_num;
	t_aabb_objects	left_objects;
	t_aabb_objects	right_objects;

	axis = 0;
	best_sah = INFINITY;
	while (axis < AXIS_NUM)
	{
		split_num = 1;
		while (split_num < BUCKETS)
		{
			t_split split = kd_split(root_aabb, axis, split_num);
			t_aabb	left_aabb = root_aabb;
			t_aabb	right_aabb = root_aabb;

			left_aabb.bounds.max = split.s.max;
			right_aabb.bounds.min = split.s.min;

			left_objects = kd_get_objects_in_aabb(left_aabb, all_aabbs, root_objects);
			right_objects = kd_get_objects_in_aabb(right_aabb, all_aabbs, root_objects);

			float	sah = EMPTY_COST
					+ (float)left_objects.num * kd_get_aabb_area(left_aabb)
					+ (float)right_objects.num * kd_get_aabb_area(right_aabb);

			if (sah < best_sah)
			{
				best_sah = sah;
				*out_left_aabb = left_aabb;
				*out_right_aabb = right_aabb;
				*out_left_objects = left_objects;
				*out_right_objects = right_objects;
			}
			split_num++;
		}
		axis++;
	}
	return best_sah;
}

void		build_kd_tree_recursive(t_kd_tree *tree, t_aabb *all_aabbs, int level)
{
	tree->left = NULL;
	tree->right = NULL;

	if (level >= KD_MAX_HEIGHT)
		return;

	t_aabb	left_aabb;
	t_aabb	right_aabb;

	t_aabb_objects	left_objects;
	t_aabb_objects	right_objects;

	float	sah = kd_split_buckets_sah(tree->aabb, &tree->objects,
			all_aabbs, &left_aabb, &right_aabb, &left_objects, &right_objects);
	if (sah > tree->sah)
		return;

	tree->objects.num = NOT_SET;
	free(tree->objects.indices);

	tree->left = rt_safe_malloc(sizeof(t_kd_tree));
	tree->left->objects = left_objects;
	tree->left->aabb = left_aabb;
	tree->left->sah = kd_get_aabb_area(left_aabb) * (float)left_objects.num;
	build_kd_tree_recursive(tree->left, all_aabbs, level + 1);

	tree->right = rt_safe_malloc(sizeof(t_kd_tree));
	tree->right->objects = right_objects;
	tree->right->aabb = right_aabb;
	tree->right->sah = kd_get_aabb_area(right_aabb) * (float) right_objects.num;
	build_kd_tree_recursive(tree->right, all_aabbs, level + 1);
}

t_aabb_objects	get_root_aabb_objects(t_aabb *all_aabbs, int num_aabbs)
{
	t_aabb_objects	aabb_objects;
	int		i;

	i = 0;
	aabb_objects.num = num_aabbs;
	aabb_objects.indices = rt_safe_malloc(sizeof(int) * num_aabbs);
	while (i < num_aabbs)
	{
		aabb_objects.indices[i] = i;
		i++;
	}
	return (aabb_objects);
}

t_kd_tree	*build_kd_tree(t_aabb *all_aabbs, int num_aabbs)
{
	t_kd_tree	*root;

	root = rt_safe_malloc(sizeof(t_kd_tree));
	root->aabb = get_root_aabb(all_aabbs, num_aabbs);
	root->sah = INFINITY;
	root->objects = get_root_aabb_objects(all_aabbs, num_aabbs);
	build_kd_tree_recursive(root, all_aabbs, 0);
	return (root);
}
