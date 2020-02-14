#include "rt.h"
#include "rt_debug.h"

void		rt_pack_kd_object_indices(t_kd_info *kd_info)
{
	cl_int	offset;
	int		i;
	int		j;

	kd_info->indices = rt_safe_malloc(sizeof(cl_int) * kd_info->indices_num);
	offset = 0;
	i = 0;
	while (i < kd_info->nodes_num)
	{
		j = 0;
		while (j < kd_info->tree_arr[i].objects.num)
		{
			kd_info->indices[j + offset] = kd_info->tree_arr[i].objects.indices[j];
			j++;
		}
		kd_info->tree_arr[i].obj_offset = offset;
		offset += j;
		i++;
	}
//	for (int k = 0; k < kd_info->indices_num; ++k)
//	{
//		printf("[%i] ", kd_info->indices[k]);
//	}
//	printf("\noffsets:\n");
//	for (int l = 0; l < kd_info->nodes_num; ++l)
//	{
//		if (kd_info->tree_arr[l].objects.num > 0)
//			printf("{%i} ", kd_info->tree_arr[l].obj_offset);
//		if (kd_info->tree_arr[l].obj_offset == 8)
//		{
//			printf("\n");
//			print_kd_arr_node(&kd_info->tree_arr[l]);
//		}
//	}
//	printf("\n");
}
