#include "test_kd_tree_header.h"
#include "test_header.h"

int			kd_get_split_axis(t_bounds bounds)
{
	float		x_bound = fabsf(bounds.b[0].x) + fabsf(bounds.b[1].x);
	float		y_bound = fabsf(bounds.b[0].y) + fabsf(bounds.b[2].y);

	return	x_bound > y_bound ? X_AXIS : Y_AXIS; //x == 0, y == 1, z == 2 (потом)
}

