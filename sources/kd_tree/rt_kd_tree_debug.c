#include "rt_debug.h"
#include "rt_kd_tree.h"

int		int_cmpfunc(const int *a, const int *b)
{
	return *a - *b;
}

void	rt_print_kd_tree_info(t_kd_info *kd_info)
{
	int		max_tris_in_node = 0;
	int		avg_tris_in_node = 0;
	int		avg_tris_in_non_empty_node = 0;
	int		median_tris_in_node = 0;

	int		empty_nodes = 0;
	int		filled_nodes = 0;
	int		nodes_with_zero_tris = 0;
	int		nodes_with_one_tris = 0;

	int		*sort_objects_num = rt_safe_malloc(sizeof(int) * kd_info->nodes_num);

	for (int i = 0; i < kd_info->nodes_num; ++i)
	{
		if (kd_info->tree_arr[i].objects.num > 0)
		{
			max_tris_in_node = ft_max(max_tris_in_node, kd_info->tree_arr[i].objects.num);
			avg_tris_in_node += kd_info->tree_arr[i].objects.num;
			sort_objects_num[filled_nodes] = kd_info->tree_arr[i].objects.num;
			filled_nodes++;
		}
		else
			empty_nodes++;
		if (kd_info->tree_arr[i].objects.num == 0)
		{
//			printf("zero tris node, index left [%i] right [%i]\n",
//					kd_info->tree_arr[i].left_index, kd_info->tree_arr[i].right_index);
			nodes_with_zero_tris++;
		}
		if (kd_info->tree_arr[i].objects.num == 1)
			nodes_with_one_tris++;
	}

	qsort(sort_objects_num, filled_nodes, sizeof(int), (__compar_fn_t)int_cmpfunc);
	for (int j = 0; j < filled_nodes; ++j)
	{
		printf("%i\n", sort_objects_num[j]);
	}


	avg_tris_in_non_empty_node = avg_tris_in_node;
	avg_tris_in_node /= kd_info->nodes_num;
	avg_tris_in_non_empty_node /= filled_nodes;
	printf("EMPTY_COST: [%.4f], BUCKETS: [%i]\n", (double)EMPTY_COST, BUCKETS);
	printf("kd-tree indices num: [%i]\n", kd_info->indices_num);
	printf("kd-tree nodes num: [%i]\n", kd_info->nodes_num);

	printf("max tris in node: [%i]\n", max_tris_in_node);
	printf("average tris in all nodes: [%i]\n", avg_tris_in_node);
	printf("average tris in non-empty nodes: [%i]\n", avg_tris_in_non_empty_node);
	printf("median of nodes num: [%i]\n", sort_objects_num[filled_nodes / 2]);
	printf("empty nodes: [%i], nodes with triangles: [%i], %% of empty nodes: [%.1f]\n",
			empty_nodes, filled_nodes, empty_nodes / ((double)kd_info->nodes_num / 100));
	printf("nodes with 0 triangles: [%i]\n", nodes_with_zero_tris);
	printf("nodes with one triangle: [%i]\n", nodes_with_one_tris);

	printf("\n");

	free(sort_objects_num);
}
