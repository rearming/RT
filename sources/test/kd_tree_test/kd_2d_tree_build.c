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

int			kd_count_obj_in_bounds(t_kd_obj *objs, t_bounds box_bounds)
{
	int		obj_in_bounds;

	obj_in_bounds = 0;
	for (int i = 0; i < HEIGHT * WIDTH; ++i)
	{
		if (objs[i].index != NOT_SET && kd_is_obj_in_bounds(objs[i].bounds, box_bounds))
			obj_in_bounds++;
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

int			comp_min_x(const t_kd_obj *object1, const t_kd_obj *object2)
{
//	return (object1->bounds.b[0].x, );
}

t_split		kd_split_sort_sah(t_bounds bounds, t_kd_obj *objects)
{
//	for (int i = 0; i < AXIS; ++i)
//		qsort(objects, sizeof(t_kd_obj) * HEIGHT * WIDTH, sizeof(t_kd_obj), );

}

float		get_surface_area(t_bounds bounds)
{
	return (fabsf(bounds.b[0].x - bounds.b[1].x) * fabsf(bounds.b[0].y - bounds.b[2].y));
}

float		calc_sah(t_kd_obj *objects, t_bounds left_bounds, t_bounds right_bounds)
{
	return EMPTY_COST + (float)kd_count_obj_in_bounds(objects, left_bounds) * get_surface_area(left_bounds)
	+ (float)kd_count_obj_in_bounds(objects, right_bounds) * get_surface_area(right_bounds);
}

t_split		kd_split_buckets_sah(t_bounds bounds, t_kd_obj *objects, t_bounds *out_left_bounds, t_bounds *out_right_bounds)
{
	t_split		best_split = (t_split){.s[0] = {}, .s[1] = {}};
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
				best_split = split;
				*out_left_bounds = left_bounds;
				*out_right_bounds = right_bounds;
			}
		}
	}
	return best_split;
}

void build_kd_tree(t_kd_tree **tree, t_bounds bounds, t_kd_obj *objects, int level)
{
	int		obj_num = kd_count_obj_in_bounds(objects, bounds);
	if (!tree || level >= MAX_HEIGHT || obj_num <= MIN_OBJ_IN_LEAF)
 		return;
	// можно также сделать return если новый bounding_box мало отличается от родительского (допустим, меньше него всего в 1.5 - 2 раза)

	t_kd_tree	*node;
	t_bounds	left_bounds;
	t_bounds	right_bounds;
//	int			left_obj_num;
//	int 		right_obj_num;
	t_split		split;
	int			split_axis;


	node = rt_safe_malloc(sizeof(t_kd_tree));
	node->bounds = bounds;
	node->obj_num = obj_num;

//	split_axis = kd_get_split_axis(bounds);
	split = kd_split_buckets_sah(bounds, objects, &left_bounds, &right_bounds);
//	split = kd_split(bounds, split_axis, 2);
//	left_bounds = kd_get_bounds(bounds, split, KD_LEFT, split_axis);
//	right_bounds = kd_get_bounds(bounds, split, KD_RIGHT, split_axis);

	*tree = node;
	build_kd_tree(&(*tree)->left, left_bounds, objects, level + 1);
	build_kd_tree(&(*tree)->right, right_bounds, objects, level + 1);
}
