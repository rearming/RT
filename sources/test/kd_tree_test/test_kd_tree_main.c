#include "test_header.h"
#include "test_kd_tree_header.h"

t_bounds		get_start_bounds(t_kd_obj *objects)
{
	t_bounds	bounds;

//	ft_bzero(&bounds, sizeof(bounds));
	bounds = (t_bounds){.n.bound0 = {{0, 0}}, .n.bound1 = {{0, 0}}, .n.bound2 = {{0, 0}}, .n.bound3 = {{0, 0}}};
	for (int i = 0; i < KD_SCENE_SIZE; ++i)
	{
		bounds.b[0].x = fminf(bounds.b[0].x, objects[0].bounds.b[0].x);
		bounds.b[0].y = fminf(bounds.b[0].y, objects[0].bounds.b[0].y);

		bounds.b[1].x = fmaxf(bounds.b[1].x, objects[i].bounds.b[1].x);
		bounds.b[1].y = fminf(bounds.b[1].y, objects[0].bounds.b[1].y);

		bounds.b[2].x = fminf(bounds.b[2].x, objects[i].bounds.b[2].x);
		bounds.b[2].y = fmaxf(bounds.b[2].y, objects[i].bounds.b[2].y);

		bounds.b[3].x = fmaxf(bounds.b[3].x, objects[i].bounds.b[3].x);
		bounds.b[3].y = fmaxf(bounds.b[3].y, objects[i].bounds.b[3].y);
	}
	bounds.b[0].x -= 0.5f;
	bounds.b[0].y -= 0.5f;
	bounds.b[1].x += 0.5f;
	bounds.b[1].y -= 0.5f;
	bounds.b[2].x -= 0.5f;
	bounds.b[2].y += 0.5f;
	bounds.b[3].x += 0.5f;
	bounds.b[3].y += 0.5f;
	return bounds;
}

t_kd_obj		g_test_kd_scene[KD_SCENE_HEIGHT][KD_SCENE_WIDTH] = {
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = 0}, {.index = -1}, {.index = -1}, {.index = 0}, {.index = -1}},
		{{.index = 0}, {.index = -1}, {.index = -1}, {.index = 0}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = -1}},
		{{.index = -1}, {.index = 0}, {.index = -1}, {.index = -1}, {.index = -1}, {.index = 0}, {.index = -1}},
		{{.index = -1}, {.index = -1}, {.index = -1}, {.index = 0}, {.index = -1}, {.index = -1}, {.index = -1}},
};

t_kd_obj		*get_1d_objects_arr(void)
{
	t_kd_obj	*objects = rt_safe_malloc(sizeof(t_kd_obj) * KD_SCENE_HEIGHT * KD_SCENE_WIDTH);
	for (int i = 0; i < KD_SCENE_HEIGHT; ++i)
	{
		for (int j = 0; j < KD_SCENE_WIDTH; ++j)
		{
			objects[j + i * KD_SCENE_WIDTH] = g_test_kd_scene[i][j];
		}
	}
	return objects;
}

void		start_build_kd_tree(t_kd_obj *objects)
{
	t_kd_tree	*root;

	root = rt_safe_malloc(sizeof(t_kd_tree));
	root->bounds = get_start_bounds(objects);
	root->left = NULL;
	root->right = NULL;
	root->sah = INFINITY;
	root->obj_num = kd_count_obj_in_bounds(objects, root->bounds, root->indices);

	build_kd_tree(root, objects, 0);


	graphic_print_kd_tree(root, objects);

	free_btree((t_avl_tree*)root, NULL);
	kd_print_bounds(root->bounds);
//	ft_printf("\n<------------------------------->\n");
//	ft_printf("max height: [%i]\n", g_max_height);
//	print_kd_tree(root);
}

void 			test_kd_tree_main(void)
{
	kd_fill_positions();

	t_kd_obj	*objects = get_1d_objects_arr();

	start_build_kd_tree(objects);
	kd_draw_loop(objects);
	free(objects);
}
