#include "../test_header.h"
#include "test_kd_tree_header.h"

/*
 * 	pos = 	0
 *
**	bounds: 0 1
 * 			2 3
*/

static inline void get_kd_obj_bounds(t_kd_obj *kd_obj)
{
	kd_obj->bounds.b[0] = kd_obj->pos;
	kd_obj->bounds.b[1] = (cl_float2){.x = kd_obj->pos.x + 1, .y = kd_obj->pos.y};
	kd_obj->bounds.b[2] = (cl_float2){.x = kd_obj->pos.x, .y = kd_obj->pos.y + 1};
	kd_obj->bounds.b[3] = (cl_float2){.x = kd_obj->pos.x + 1, .y = kd_obj->pos.y + 1};
}

void		kd_fill_positions(void)
{
	int		index;

	index = 0;
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (g_test_kd_scene[y][x].index != -1)
				g_test_kd_scene[y][x].index = ++index;
			g_test_kd_scene[y][x].pos = (cl_float2){.x = x, .y = y};
			get_kd_obj_bounds(&g_test_kd_scene[y][x]);
//			printf("x: [%i] y: [%i]\n", g_test_kd_scene[y][x].pos.x, g_test_kd_scene[y][x].pos.y);
		}
	}
}

void		kd_print_scene(void)
{
	printf("  x →");
	for (int x = 0; x < WIDTH; ++x)
		printf(" %i", x);
	printf("\ny\n↓\n");
	for (int y = 0; y < HEIGHT; ++y)
	{
		printf("%i\t ", y);
		for (int x = 0; x < WIDTH; ++x)
			printf(" %c", g_test_kd_scene[y][x].index == -1 ? '.' : 'X');
		printf("\n");
	}
}

void	print_cl_float2(cl_float2 vec)
{
	ft_printf("x: [%.2f], y: [%.2f]\n", vec.x, vec.y);
}

void	kd_print_node(t_kd_tree *node)
{
	ft_printf("obj num: [%i]\n", node->obj_num);
	for (int i = 0; i < BOUNDS_NUM; ++i)
	{
		ft_printf("bounds[%i]: ", i);
		print_cl_float2(node->bounds.b[i]);
	}
	ft_printf("\n");
}

void	print_kd_tree(t_kd_tree *root, int level)
{
	if (!root)
		return;
	ft_printf("node's level: [%i]\n", level);
	kd_print_node(root);
	print_kd_tree(root->left, level + 1);
	print_kd_tree(root->right, level + 1);
}
