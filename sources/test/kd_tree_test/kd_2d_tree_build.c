#include "test_header.h"
#include "test_kd_tree_header.h"

bool		kd_is_obj_in_bounds(t_bounds obj_bounds, t_bounds box_bounds)
{
	for (int bound = 0; bound < BOUNDS_NUM; ++bound)
	{
		if (obj_bounds.b[bound].x > box_bounds.b[0].x && obj_bounds.b[bound].x < box_bounds.b[1].x
		&& obj_bounds.b[bound].y > box_bounds.b[0].y && obj_bounds.b[bound].y < box_bounds.b[2].y)
			return true;
	}
	return false;
}

int		kd_count_obj_in_bounds(t_kd_obj *objs, t_bounds box_bounds, int out_indices[MAX_OBJ_IN_LEAF])
{
	int		obj_in_bounds;

	obj_in_bounds = 0;
	if (out_indices)
		for (int j = 0; j < MAX_OBJ_IN_LEAF; ++j)
			out_indices[j] = NOT_SET;
	for (int i = 0; i < KD_SCENE_HEIGHT * KD_SCENE_WIDTH; ++i)
	{
		if (objs[i].index != NOT_SET && kd_is_obj_in_bounds(objs[i].bounds, box_bounds))
		{
			if (obj_in_bounds < MAX_OBJ_IN_LEAF && out_indices)
				out_indices[obj_in_bounds] = objs[i].index;
			obj_in_bounds++;
		}
	}
	return obj_in_bounds;
}

t_split		kd_split(t_bounds bounds, int axis, int parts)
{
	t_split		split;

	if (axis == X_AXIS)
	{
		split.n.split0 = (cl_float2){.x = (bounds.n.bound0.x + bounds.n.bound1.x) / (float)parts, .y = bounds.n.bound0.y};
		split.n.split1 = (cl_float2){.x = (bounds.n.bound0.x + bounds.n.bound1.x) / (float)parts, .y = bounds.n.bound2.y};
	}
	else // Y_AXIS
	{
		split.n.split0 = (cl_float2){.x = bounds.n.bound0.x, .y = (bounds.n.bound0.y + bounds.n.bound2.y) / (float)parts};
		split.n.split1 = (cl_float2){.x = bounds.n.bound1.x, .y = (bounds.n.bound0.y + bounds.n.bound2.y) / (float)parts};;
	}
	return split;
}

t_bounds	kd_get_bounds(t_bounds prev_bounds, t_split split, int side, int axis)
{
	t_bounds	bounds;

	bounds = prev_bounds;
	if (side == KD_LEFT)
	{
		if (axis == X_AXIS)
		{
			bounds.n.bound1 = split.n.split0;
			bounds.n.bound3 = split.n.split1;
		}
		else
		{
			bounds.n.bound2 = split.n.split0;
			bounds.n.bound3 = split.n.split1;
		}
	}
	else // side == KD_RIGHT
	{
		if (axis == X_AXIS)
		{
			bounds.n.bound0 = split.n.split0;
			bounds.n.bound2 = split.n.split1;
		}
		else
		{
			bounds.n.bound0 = split.n.split0;
			bounds.n.bound1 = split.n.split1;
		}
	}
	return bounds;
}

float		get_surface_area(t_bounds bounds)
{
	return (fabsf(bounds.b[0].x - bounds.b[1].x) * fabsf(bounds.b[0].y - bounds.b[2].y));
}

float		calc_sah(t_kd_obj *objects, t_bounds left_bounds, t_bounds right_bounds)
{
	return EMPTY_COST + (float) kd_count_obj_in_bounds(objects, left_bounds,NULL) * get_surface_area(left_bounds)
	+ (float) kd_count_obj_in_bounds(objects, right_bounds, NULL) * get_surface_area(right_bounds);
}

float kd_split_buckets_sah(t_bounds bounds, t_kd_obj *objects, t_bounds *out_left_bounds, t_bounds *out_right_bounds)
{
	float		best_sah = INFINITY;

	for (int i = 0; i < AXIS; ++i)
	{
		t_split		one_bucket = kd_split(bounds, i, BUCKETS);
		for (int j = 1; j < BUCKETS; ++j)
		{
			t_bounds	left_bounds;
			t_bounds	right_bounds;

			t_split		split;
			if (i == X_AXIS)
			{
				split.s[0] = (cl_float2){.x = one_bucket.s[0].x * (float)j, .y = one_bucket.s[0].y};
				split.s[1] = (cl_float2){.x = one_bucket.s[1].x * (float)j, .y = one_bucket.s[1].y};
			}
			else // if (i == Y_AXIS)
			{
				split.s[0] = (cl_float2){.x = one_bucket.s[0].x, .y = one_bucket.s[0].y * (float)j};
				split.s[1] = (cl_float2){.x = one_bucket.s[1].x, .y = one_bucket.s[1].y * (float)j};
			}
			left_bounds = kd_get_bounds(bounds, split, KD_LEFT, i);
			right_bounds = kd_get_bounds(bounds, split, KD_RIGHT, i);

			float		sah = calc_sah(objects, left_bounds, right_bounds);
			if (sah < best_sah)
			{
				best_sah = sah;
				*out_left_bounds = left_bounds;
				*out_right_bounds = right_bounds;
			}
		}
	}
	return best_sah;
}

int			kd_find_matches(const int left_indices[MAX_OBJ_IN_LEAF], const int right_indices[MAX_OBJ_IN_LEAF])
{
	int		matches = 0;

	for (int i = 0; i < MAX_OBJ_IN_LEAF; ++i)
	{
		for (int j = 0; j < MAX_OBJ_IN_LEAF; ++j)
		{
			if (left_indices[i] != NOT_SET && right_indices[i] != NOT_SET
			&& left_indices[i] == right_indices[j])
				matches++;
		}
	}
	return matches;
}

void		build_kd_tree(t_kd_tree *tree, t_kd_obj *objects, int level)
{
	if (!tree)
		return;
	tree->left = NULL;
	tree->right = NULL;

	if (level >= g_max_height || tree->obj_num <= MIN_OBJ_IN_LEAF)
		return;

	t_bounds left_bounds;
	t_bounds right_bounds;

	float sah = kd_split_buckets_sah(tree->bounds, objects, &left_bounds, &right_bounds);
	if (sah / tree->sah > 0.8f)
		return;

	int left_obj_indices[MAX_OBJ_IN_LEAF];
	int right_obj_indices[MAX_OBJ_IN_LEAF];

	int left_obj_num = kd_count_obj_in_bounds(objects, left_bounds,
			left_obj_indices);
	int right_obj_num = kd_count_obj_in_bounds(objects, right_bounds,
			right_obj_indices);

	int	matches = kd_find_matches(left_obj_indices, right_obj_indices);

	if (((float) matches / (float) left_obj_num > 0.8f
	|| (float) matches / (float) right_obj_num > 0.8f))
		return; //todo проверить, нужно ли (если да - какой оптимальный коеффициент)

	tree->left = rt_safe_malloc(sizeof(t_kd_tree));
	tree->left->obj_num = left_obj_num;
	tree->left->bounds = left_bounds;
	tree->left->sah = sah;
	ft_memcpy(tree->left->indices, left_obj_indices, sizeof(int) * MAX_OBJ_IN_LEAF);
	build_kd_tree(tree->left, objects, level + 1);

	tree->right = rt_safe_malloc(sizeof(t_kd_tree));
	tree->right->obj_num = right_obj_num;
	tree->right->bounds = right_bounds;
	tree->right->sah = sah;
	ft_memcpy(tree->right->indices, right_obj_indices, sizeof(int) * MAX_OBJ_IN_LEAF);
	build_kd_tree(tree->right, objects, level + 1);
}
