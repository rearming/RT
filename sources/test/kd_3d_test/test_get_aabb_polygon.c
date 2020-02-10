#include <rt_debug.h>
#include "test_header.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"

void	print_all_aabbs(t_aabb *aabbs, int num_aabb)
{
	for (int i = 0; i < num_aabb; ++i)
	{
		rt_print_clfloat3(aabbs->bounds.min, "min");
		rt_print_clfloat3(aabbs->bounds.max, "max");
	}
}

void	test_get_aabb_polygons(void)
{
	t_meshes		meshes;
	t_aabb			*aabbs;

	rt_load_obj_files(&meshes);
	aabbs = rt_get_all_aabbs(&meshes);
	rt_print_parsed_polygon(&meshes.polygons[0]);
	print_all_aabbs(aabbs, meshes.num_polygons);
}
