#include <time.h>
#include "../test_header.h"
#include "test_kd_tree_header.h"

/*
 * 	pos = 	0
 *
**	bounds: 0 1
 * 			2 3
*/

#ifdef __APPLE__
# define scene_random arc4random
#else
# define scene_random rand
#endif

static inline void get_kd_obj_bounds(t_kd_obj *kd_obj)
{
	srand(time(NULL));
	float		size = (float)drand48() * 2;
	kd_obj->bounds.arr[0] = kd_obj->pos;
	kd_obj->bounds.arr[1] = (cl_float2){.x = kd_obj->pos.x + size, .y = kd_obj->pos.y};
	kd_obj->bounds.arr[2] = (cl_float2){.x = kd_obj->pos.x, .y = kd_obj->pos.y + size};
	kd_obj->bounds.arr[3] = (cl_float2){.x = kd_obj->pos.x + size, .y = kd_obj->pos.y + size};
}

void		kd_2d_fill_positions(void)
{
	int		index;

	index = 0;
	for (int y = 0; y < KD_SCENE_HEIGHT; ++y)
	{
		for (int x = 0; x < KD_SCENE_WIDTH; ++x)
		{
			if (g_test_kd_scene[y][x].index != NOT_SET)
			{
				g_test_kd_scene[y][x].index = ++index;
			}
			g_test_kd_scene[y][x].pos = (cl_float2){.x = x, .y = y};
			get_kd_obj_bounds(&g_test_kd_scene[y][x]);
//			printf("x: [%i] y: [%i]\n", g_test_kd_scene[y][x].pos.x, g_test_kd_scene[y][x].pos.y);
		}
	}
}

void		kd_2d_print_scene(void)
{
	printf("  x →");
	for (int x = 0; x < KD_SCENE_WIDTH; ++x)
		printf(" %i", x);
	printf("\ny\n↓\n");
	for (int y = 0; y < KD_SCENE_HEIGHT; ++y)
	{
		printf("%i\t ", y);
		for (int x = 0; x < KD_SCENE_WIDTH; ++x)
			printf(" %c", g_test_kd_scene[y][x].index == -1 ? '.' : 'X');
		printf("\n");
	}
}

void	print_cl_float2(cl_float2 vec)
{
	ft_printf("x: [%.2f], y: [%.2f]\n", vec.x, vec.y);
}

void	kd_2d_print_bounds(t_bounds bounds)
{
	for (int i = 0; i < BOUNDS_NUM; ++i)
	{
		ft_printf("bounds[%i]: ", i);
		print_cl_float2(bounds.arr[i]);
	}
}

void	kd_2d_print_node(t_kd_tree *node)
{
	ft_printf("obj num: [%i]\n", node->obj_num);
	kd_2d_print_bounds(node->bounds);
	if (node->indices[0] != NOT_SET)
	{
		ft_printf("obj indices:\n");
		for (int j = 0; j < MAX_OBJ_IN_LEAF; ++j)
			ft_printf("[%i] ", node->indices[j]);
	}
	ft_printf("\n\n");
}

int		g_2d_nodes_num = 0;

void 	print_2d_kd_traverse(t_kd_tree *root, int level)
{
	if (!root)
		return;
	ft_printf("node's level: [%i]\n", level);
//	ft_printf("nodes num now: [%i]\n", g_2d_nodes_num);
	kd_2d_print_node(root);
	g_2d_nodes_num++;
	print_2d_kd_traverse(root->left, level + 1);
	print_2d_kd_traverse(root->right, level + 1);
}

void	print_2d_kd_tree(t_kd_tree *root)
{
	g_2d_nodes_num = 0;
	print_2d_kd_traverse(root, 0);
	ft_printf("nodes number: [%i]\n", g_2d_nodes_num);
}


