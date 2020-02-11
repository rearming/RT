#include "test_header.h"
#include "kd_2d_tree_header.h"
#include "rt_math_utils.h"

t_aabb		*kd_2d_get_test_objects(int *out_aabbs_num)
{
	int			aabbs_num = 2;
	t_aabb		*aabbs;

	aabbs = rt_safe_malloc(sizeof(t_aabb) * aabbs_num);
	*out_aabbs_num = aabbs_num;
	aabbs[0] = (t_aabb){.bounds = {.min = (cl_float2){{1, 1}}, .max = (cl_float2){{2, 2}}}};
	aabbs[1] = (t_aabb){.bounds = {.min = (cl_float2){{-3, -1}}, .max = (cl_float2){{-2, 1}}}};
	return (aabbs);
}

t_aabb		get_2d_root_aabb(t_aabb *obj_aabbs, int num_aabbs)
{
	t_aabb	root_aabb;
	int		i = 0;

	root_aabb.bounds.min = (cl_float2){{INFINITY, INFINITY}};
	root_aabb.bounds.max = (cl_float2){{-INFINITY, -INFINITY}};
	while (i < num_aabbs)
	{
		root_aabb.bounds.min = fmin_float2(root_aabb.bounds.min, obj_aabbs[i].bounds.min);
		root_aabb.bounds.max = fmax_float2(root_aabb.bounds.max, obj_aabbs[i].bounds.max);
		i++;
	}
	return (root_aabb);
}

void		start_build_kd_2d_tree(t_aabb *obj_aabbs, int num_aabbs)
{
	t_kd_tree	*root;

	root = build_2d_kd_tree(obj_aabbs, num_aabbs);

	graphic_print_kd_tree(root, obj_aabbs, num_aabbs);

//	kd_2d_print_bounds(root->bounds);
	ft_printf("\n<------------------------------->\n");
//	ft_printf("max height: [%i]\n", g_max_height);
	print_2d_kd_tree(root);

	free_btree((t_avl_tree*)root, NULL);
}

void 			test_kd_2d_tree_main(void)
{
	int		num_aabbs;
	t_aabb 	*obj_aabbs = kd_2d_get_test_objects(&num_aabbs);

	g_max_height = 0;
	start_build_kd_2d_tree(obj_aabbs, num_aabbs);
	kd_draw_loop(obj_aabbs, num_aabbs);
	free(obj_aabbs);
}
