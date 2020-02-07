#include "test_header.h"
#include "test_kd_tree_header.h"

t_kd_obj		g_test_kd_scene[HEIGHT][WIDTH] = {
		{{.index = 0}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = 0}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
};

void 			test_kd_tree_main(void)
{
	kd_fill_positions();
	kd_print_scene();
	t_kd_tree	*root;

	root = rt_safe_malloc(sizeof(t_kd_tree));
	root->bounds[0] = (cl_float2){.x = 0, .y = 0};
	root->bounds[1] = (cl_float2){.x = WIDTH, .y = 0};
	root->bounds[2] = (cl_float2){.x = 0, .y = HEIGHT};
	root->bounds[3] = (cl_float2){.x = WIDTH, .y = HEIGHT};
	root->left = NULL;
	root->right = NULL;

	build_kd_tree(&root, 0);
}
