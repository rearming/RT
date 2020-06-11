#ifndef RT_KD_TREE_BUILD_H
# define RT_KD_TREE_BUILD_H

float		kd_split_buckets_sah(t_aabb root_aabb,
		t_aabb_objects *root_objects,
		t_aabb *all_aabbs,
		t_aabb *out_left_aabb,
		t_aabb *out_right_aabb,
		t_aabb_objects *out_left_objects,
		t_aabb_objects *out_right_objects,
		float *out_split,
		int *out_split_axis);

void		build_kd_tree_recursive(
		t_kd_tree *tree,
		t_aabb *all_aabbs,
		int level,
		int *index);

typedef struct	s_kd_split_buckets_params
{
	t_aabb			root_aabb;
	t_aabb_objects	root_objects;
	t_aabb			all_aabbs;
	t_aabb			out_left_aabb;
	t_aabb			out_right_aabb;
	t_aabb_objects	out_left_objects;
	t_aabb_objects	out_right_objects;
	float			out_split;
	int				out_split_axis;
}				s_kd_split_buckets_params;

#endif
