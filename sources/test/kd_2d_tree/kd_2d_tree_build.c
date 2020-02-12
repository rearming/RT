#include "rt.h"
#include "kd_2d_tree_header.h"

int			kd_2d_find_matches(const int *left_indices, const int *right_indices)
{
	int		matches;
	int		i;
	int		j;

	i = 0;
	matches = 0;
	while (i < KD_MAX_OBJ_IN_LEAF)
	{
		j = 0;
		while (j < KD_MAX_OBJ_IN_LEAF)
		{
			if (left_indices[i] != NOT_SET && right_indices[i] != NOT_SET
				&& left_indices[i] == right_indices[j])
				matches++;
			j++;
		}
		i++;
	}
	return (matches);
}

void		rt_kd_2d_unset_indices(int *indices)
{
	if (!indices)
		return;
	indices[0] = NOT_SET;
	indices[1] = NOT_SET;
	indices[2] = NOT_SET;
}

t_split		kd_2d_split(t_aabb root_aabb, int axis, int split_num)
{
	t_split		split;

	split.s.min = root_aabb.bounds.min;
	split.s.min.s[axis] = root_aabb.bounds.min.s[axis] + ((root_aabb.bounds.max.s[axis] - root_aabb.bounds.min.s[axis]) / BUCKETS) * (float)split_num;
	split.s.max = root_aabb.bounds.max;
	split.s.max.s[axis] = split.s.min.s[axis]; // координата разделения та же, бокс выровнен по осям
	return (split);
}

bool		kd_2d_is_obj_in_aabb(t_aabb root_aabb, t_aabb obj_aabb)
{
	if ((obj_aabb.bounds.min.x < root_aabb.bounds.max.x
		 && obj_aabb.bounds.min.y < root_aabb.bounds.max.y
		 && obj_aabb.bounds.max.x > root_aabb.bounds.min.x
		 && obj_aabb.bounds.max.y > root_aabb.bounds.min.y)
		||
		(obj_aabb.bounds.max.x > root_aabb.bounds.min.x
		&& obj_aabb.bounds.max.y > root_aabb.bounds.min.y
		&& obj_aabb.bounds.min.x < root_aabb.bounds.max.x
		&& obj_aabb.bounds.min.y < root_aabb.bounds.max.y))
		return true;
	return false;
}

int			kd_2d_count_obj_in_aabb(t_aabb aabb, t_aabb *obj_aabbs, int num_aabbs, int *out_indices)
{
	int		obj_in_bounds;
	int		i;

	obj_in_bounds = 0;
	i = 0;
	rt_kd_2d_unset_indices(out_indices);
	while (i < num_aabbs)
	{
		if (kd_2d_is_obj_in_aabb(aabb, obj_aabbs[i]))
		{
			if (obj_in_bounds < KD_MAX_OBJ_IN_LEAF && out_indices)
				out_indices[obj_in_bounds] = i; // тут i == индексу полигона
			obj_in_bounds++;
		}
		i++;
	}
	if (obj_in_bounds >= KD_MAX_OBJ_IN_LEAF && out_indices)
		rt_kd_2d_unset_indices(out_indices);
	return obj_in_bounds;
}

float		kd_2d_get_aabb_area(t_aabb aabb)
{
	return (fabsf(aabb.bounds.min.x - aabb.bounds.max.x)
			* fabsf(aabb.bounds.min.y - aabb.bounds.max.y));
}

float		calc_2d_sah(t_aabb *obj_aabbs, int num_aabbs, t_aabb left_bounds, t_aabb right_bounds)
{
//	int		left_obj_indices[KD_MAX_OBJ_IN_LEAF];
//	int		right_obj_indices[KD_MAX_OBJ_IN_LEAF];
//
//	int		left_obj_num = kd_2d_count_obj_in_aabb(tree->aabb, obj_aabbs,
//			num_aabbs, left_obj_indices);
//	int		right_obj_num = kd_2d_count_obj_in_aabb(tree->aabb, obj_aabbs,
//			num_aabbs, right_obj_indices);
//
//	int		matches = kd_2d_find_matches(left_obj_indices, right_obj_indices);

//	if (((float) matches / (float) left_obj_num > 0.5f
//		 || (float) matches / (float) right_obj_num > 0.5f))
//		return;
	return g_empty_cost // kd_2d_count_obj_in_aabb можно закешировать раньше (и не считать два раза)
		   + (float) kd_2d_count_obj_in_aabb(left_bounds, obj_aabbs, num_aabbs,
			NULL) *
			 kd_2d_get_aabb_area(left_bounds)
		   + (float) kd_2d_count_obj_in_aabb(right_bounds, obj_aabbs, num_aabbs,
			NULL) *
			 kd_2d_get_aabb_area(right_bounds);
}

float		kd_2d_split_buckets_sah(t_aabb root_aabb, t_aabb *obj_aabbs, int num_aabbs, t_aabb *out_left_aabb, t_aabb *out_right_aabb)
{
	float	best_sah;
	int		axis;
	int		split_num;

	axis = 0;
	best_sah = INFINITY;
	while (axis < AXIS_NUM)
	{
		split_num = 1;
		while (split_num < BUCKETS)
		{
			t_split split = kd_2d_split(root_aabb, axis, split_num);
			t_aabb	left_aabb = root_aabb;
			t_aabb	right_aabb = root_aabb;

			left_aabb.bounds.max = split.s.max;
			right_aabb.bounds.min = split.s.min;

			float	sah = calc_2d_sah(obj_aabbs, num_aabbs, left_aabb,
					right_aabb);
			if (sah < best_sah)
			{
				best_sah = sah;
				*out_left_aabb = left_aabb;
				*out_right_aabb = right_aabb;
			}
			split_num++;
		}
		axis++;
	}
	return best_sah;
}

void		build_2d_kd_tree_recursive(t_kd_tree *tree, t_aabb *obj_aabbs, int num_aabbs, int level)
{
	tree->left = NULL;
	tree->right = NULL;

	t_aabb	left_aabb;
	t_aabb	right_aabb;

	float	sah = kd_2d_split_buckets_sah(tree->aabb, obj_aabbs, num_aabbs,
			&left_aabb, &right_aabb);
	if (sah > kd_2d_get_aabb_area(tree->aabb) * (float)tree->obj_num)
		return;

	int		left_obj_indices[KD_MAX_OBJ_IN_LEAF];
	int		right_obj_indices[KD_MAX_OBJ_IN_LEAF];

	int		left_obj_num = kd_2d_count_obj_in_aabb(left_aabb, obj_aabbs,
			num_aabbs, left_obj_indices);
	int		right_obj_num = kd_2d_count_obj_in_aabb(right_aabb, obj_aabbs,
			num_aabbs, right_obj_indices);

	tree->left = rt_safe_malloc(sizeof(t_kd_tree));
	tree->left->obj_num = left_obj_num;
	tree->left->aabb = left_aabb;
	tree->left->sah = sah;
	ft_memcpy(tree->left->indices, left_obj_indices, sizeof(int) * KD_MAX_OBJ_IN_LEAF);
	build_2d_kd_tree_recursive(tree->left, obj_aabbs, num_aabbs, level + 1);

	tree->right = rt_safe_malloc(sizeof(t_kd_tree));
	tree->right->obj_num = right_obj_num;
	tree->right->aabb = right_aabb;
	tree->right->sah = sah;
	ft_memcpy(tree->right->indices, right_obj_indices, sizeof(int) * KD_MAX_OBJ_IN_LEAF);
	build_2d_kd_tree_recursive(tree->right, obj_aabbs, num_aabbs, level + 1);
}

t_kd_tree	*build_2d_kd_tree(t_aabb *obj_aabbs, int num_aabbs)
{
	t_kd_tree	*root;

	root = rt_safe_malloc(sizeof(t_kd_tree));
	root->aabb = get_2d_root_aabb(obj_aabbs, num_aabbs);
	root->sah = INFINITY;
	rt_kd_2d_unset_indices(root->indices);
	root->obj_num = kd_2d_count_obj_in_aabb(root->aabb, obj_aabbs, num_aabbs,
			root->indices);
	build_2d_kd_tree_recursive(root, obj_aabbs, num_aabbs, 0);
	return (root);
}
