#include "rt.h"
#include "rt_kd_tree.h"

bool		rt_kd_tree_import(t_kd_info *kd_info, const char *obj_path)
{
	const char		*binary_path = rt_get_kd_binary_path(obj_path);
	FILE			*fp;

	fp = fopen(binary_path, "rb");
	if (!fp)
	{
		printf("[warning] can't open kd tree binary [%s]\n", binary_path);
		free((char*)binary_path);
		return (false);
	}
	fread(&kd_info->nodes_num, sizeof(cl_int), 1, fp);
	fread(&kd_info->indices_num, sizeof(cl_int), 1, fp);
	kd_info->tree_arr = rt_safe_malloc(sizeof(t_kd_arr_tree) * kd_info->nodes_num);
	fread(kd_info->tree_arr, sizeof(t_kd_arr_tree) * kd_info->nodes_num, 1, fp);
	kd_info->indices = rt_safe_malloc(sizeof(cl_int) * kd_info->indices_num);
	fread(kd_info->indices, sizeof(cl_int) * kd_info->indices_num, 1, fp);
	free((char*)binary_path);
	fclose(fp);
	return (true);
}
