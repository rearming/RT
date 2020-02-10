#include "test_kd_tree_header.h"
#include "test_header.h"

int			kd_get_split_axis(t_bounds bounds)
{
	float		x_bound = fabsf(bounds.arr[0].x) + fabsf(bounds.arr[1].x);
	float		y_bound = fabsf(bounds.arr[0].y) + fabsf(bounds.arr[2].y);

	return	x_bound > y_bound ? X_AXIS : Y_AXIS; //x == 0, y == 1, z == 2 (потом)
}

