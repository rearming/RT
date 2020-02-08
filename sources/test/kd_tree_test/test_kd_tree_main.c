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

	build_kd_tree(&root, root_bounds, 0);
	print_kd_tree(root, 0);
}
