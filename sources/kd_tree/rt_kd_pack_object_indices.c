#include "rt.h"

void		rt_pack_kd_object_indices(t_kd_info *kd_object)
{
	cl_int	offset;
	int		i;
	int		j;

	kd_object->indices = rt_safe_malloc(sizeof(cl_int) * kd_object->indices_num);
	offset = 0;
	i = 0;
	while (i < kd_object->nodes_num)
	{
		j = 0;
		while (j < kd_object->tree_arr[i].objects.num)
		{
			kd_object->indices[j + offset] = kd_object->tree_arr[i].objects.indices[j];
			j++;
		}
		offset += j;
		kd_object->tree_arr[i].obj_offset = offset;
		i++;
	}
}
