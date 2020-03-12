#include "rt.h"
#include "rt_kd_tree.h"

t_kd_info		rt_get_kd_object(t_meshes *meshes)
{
	t_kd_info		kd_object;
	t_aabb			*all_aabbs;
	t_kd_tree		*kd_tree;
	t_kd_arr_tree	*kd_arr_tree;

	kd_object.indices_num = 0;
	kd_object.nodes_num = 0;
	all_aabbs = rt_get_all_aabbs(meshes);
	kd_tree = build_kd_tree(all_aabbs, meshes->num_polygons);
	kd_arr_tree = kd_tree_to_array(kd_tree, &kd_object.nodes_num, &kd_object.indices_num);
	free(all_aabbs);
	free_kd_tree(kd_tree, false);
	kd_object.tree_arr = kd_arr_tree;
	printf("indices num: [%i]\n", kd_object.indices_num);
	printf("nodes num: [%i]\n", kd_object.nodes_num);
	rt_pack_kd_object_indices(&kd_object);
	return (kd_object);
}
