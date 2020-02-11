#include <rt_debug.h>
#include "test_header.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"

void	test_get_aabb_polygons(void)
{
	t_meshes		meshes;
	t_aabb			*obj_aabbs;
	t_kd_tree		*kd_tree;

	rt_load_obj_files(&meshes);
	obj_aabbs = rt_get_all_aabbs(&meshes);
	kd_tree = build_kd_tree(obj_aabbs, meshes.num_polygons);
	ft_printf("k-d tree building done!\n");

	print_aabb(kd_tree->aabb);
	print_kd_tree(kd_tree);
//	rt_print_parsed_polygon(&meshes.polygons[0]);
//	print_all_aabbs(obj_aabbs, meshes.num_polygons);
//	root_aabb = get_root_aabb(obj_aabbs, meshes.num_polygons);
	free_btree((t_avl_tree*)kd_tree, NULL);
}
