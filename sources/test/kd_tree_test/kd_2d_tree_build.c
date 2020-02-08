#include "test_header.h"
#include "test_kd_tree_header.h"

cl_float2	get_max_bound(t_bounds box_bounds)
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
//			if (g_test_kd_scene[i][j].bounds.n.bound0.x < box_bounds.n.bound0.x
//			&& g_test_kd_scene[i][j].bounds.n.bound0.y > box_bounds.n.bound0.x)
		}
	}
}

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

int			kd_count_obj_in_bounds(t_kd_obj p_kd_objs[HEIGHT][WIDTH], t_bounds box_bounds)
{
	int		obj_in_bounds;

	obj_in_bounds = 0;
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (p_kd_objs[i][j].index != NOT_SET && kd_is_obj_in_bounds(p_kd_objs[i][j].bounds, box_bounds))
				obj_in_bounds++;
		}
	}
	return obj_in_bounds;
}

t_split		kd_get_split(t_bounds bounds, int axis)
{
	t_split		split;

	if (axis == X_AXIS)
	{
		split.n.split0 = (cl_float2){.x = (bounds.n.bound0.x + bounds.n.bound1.x) / 2, .y = bounds.n.bound0.y};
		split.n.split1 = (cl_float2){.x = (bounds.n.bound0.x + bounds.n.bound1.x) / 2, .y = bounds.n.bound2.y};
	}
	else // Y_AXIS
	{
		split.n.split0 = (cl_float2){.x = bounds.n.bound0.x, .y = (bounds.n.bound0.y + bounds.n.bound2.y) / 2};
		split.n.split1 = (cl_float2){.x = bounds.n.bound1.x, .y = (bounds.n.bound0.y + bounds.n.bound2.y) / 2};;
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

void		build_kd_tree(t_kd_tree **tree, t_bounds bounds, int level)
{
	if (!tree || level >= MAX_HEIGHT) // || no_object_in_bounds(bounds))
		return;
	t_kd_tree	*node;
	t_bounds	left_bounds;
	t_bounds	right_bounds;
//	int			left_obj_num;
//	int 		right_obj_num;
	t_split		split;
	int			split_axis;

	node = rt_safe_malloc(sizeof(t_kd_tree));
	node->bounds = bounds;
	node->obj_num = kd_count_obj_in_bounds(g_test_kd_scene, bounds);

	split_axis = kd_get_split_axis(bounds);
	split = kd_get_split(bounds, split_axis);
	left_bounds = kd_get_bounds(bounds, split, KD_LEFT, split_axis);
	right_bounds = kd_get_bounds(bounds, split, KD_RIGHT, split_axis);
//	left_obj_num = kd_count_obj_in_bounds(g_test_kd_scene, left_bounds);
//	right_obj_num = kd_count_obj_in_bounds(g_test_kd_scene, right_bounds);

	*tree = node;
	build_kd_tree(&(*tree)->left, left_bounds, level + 1);
	build_kd_tree(&(*tree)->right, right_bounds, level + 1);
}
