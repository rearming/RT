#include "rt.h"
#include "rt_kd_tree.h"
#include "rt_kd_tree_build.h"

t_split		kd_split(t_aabb root_aabb, int axis, int split_num)
{
	t_split		split;

	split.s.min = root_aabb.min;
	split.s.min.s[axis] = root_aabb.min.s[axis] + ((root_aabb.max.s[axis] - root_aabb.min.s[axis]) / BUCKETS) * (float)split_num;
	split.s.max = root_aabb.max;
	split.s.max.s[axis] = split.s.min.s[axis];
	return (split);
}

float		kd_split_buckets_sah(t_aabb root_aabb,
						   t_aabb_objects *root_objects,
						   t_aabb *all_aabbs,
						   t_aabb *out_left_aabb,
						   t_aabb *out_right_aabb,
						   t_aabb_objects *out_left_objects,
						   t_aabb_objects *out_right_objects,
						   float *out_split,
						   int *out_split_axis)
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

			left_aabb.max = split.s.max;
			right_aabb.min = split.s.min;

			left_objects = kd_get_objects_in_aabb(left_aabb, all_aabbs, root_objects);
			right_objects = kd_get_objects_in_aabb(right_aabb, all_aabbs, root_objects);

			float	sah = EMPTY_COST
					+ (float)left_objects.num * kd_get_aabb_area(left_aabb)
					+ (float)right_objects.num * kd_get_aabb_area(right_aabb);

			if (sah < best_sah)
			{
				if (best_sah != INFINITY)
				{
					free((*out_left_objects).indices);
					free((*out_right_objects).indices);
				}
				best_sah = sah;
				*out_left_aabb = left_aabb;
				*out_right_aabb = right_aabb;
				*out_left_objects = left_objects;
				*out_right_objects = right_objects;
				*out_split = split.s.min.s[axis]; // split.s.min.s[axis] == split.s.max.s[axis]
				*out_split_axis = axis;
			}
			else
			{
				free(left_objects.indices);
				free(right_objects.indices);
			}
			split_num++;
		}
		axis++;
	}
	return best_sah;
}

t_kd_tree	*build_kd_tree(t_aabb *all_aabbs, int num_aabbs)
{
	t_kd_tree	*root;
	int			index = 0;

	root = rt_safe_malloc(sizeof(t_kd_tree));
	root->aabb = get_root_aabb(all_aabbs, num_aabbs);
	root->sah = INFINITY;
	root->objects = get_root_aabb_objects(num_aabbs);
	build_kd_tree_recursive(root, all_aabbs, 0, &index);
	return (root);
}
