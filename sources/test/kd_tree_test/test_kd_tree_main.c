#include "test_header.h"
#include "test_kd_tree_header.h"

t_kd_obj		g_test_kd_scene[HEIGHT][WIDTH] = {
		{{.index = 0}, {.index = 0}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = 0}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = 0}},
};

t_kd_obj		*get_1d_objects_arr(void)
{
	t_kd_obj	*objects = rt_safe_malloc(sizeof(t_kd_obj) * HEIGHT * WIDTH);
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			objects[j + i * WIDTH] = g_test_kd_scene[i][j];
		}
	}
//	for (int k = 0; k < HEIGHT * WIDTH; ++k)
//	{
//		if (objects[k].index != NOT_SET)
//		{
//			ft_printf("obj[%i]: index: [%i]\n", k, objects[k].index);
//			print_cl_float2(objects[k].pos);
//		}
//	}
	return objects;
}

void 			test_kd_tree_main(void)
{
	kd_fill_positions();
	kd_print_scene();
	t_kd_tree	*root;

	t_bounds	root_bounds;

	//todo get_start_bounds(t_kd_obj **all_objects)
	root_bounds.b[0] = (cl_float2){.x = 0, .y = 0};
	root_bounds.b[1] = (cl_float2){.x = WIDTH, .y = 0};
	root_bounds.b[2] = (cl_float2){.x = 0, .y = HEIGHT};
	root_bounds.b[3] = (cl_float2){.x = WIDTH, .y = HEIGHT};

	t_kd_obj	*arr = get_1d_objects_arr();

	build_kd_tree(&root, root_bounds, arr, 0);
	print_kd_tree(root, 0);
}
