#include "rt.h"
#include "rt_kd_tree.h"

static void		write_nodes(
		t_kd_info *kd_info,
		unsigned char *bytes,
		size_t *offset)
{
	int		i;

	ft_memcpy(bytes, &kd_info->nodes_num, sizeof(cl_int));
	*offset = sizeof(cl_int) * 2;
	i = 0;
	while (i < kd_info->nodes_num)
	{
		ft_memcpy(&bytes[*offset],
				&kd_info->tree_arr[i], sizeof(t_kd_arr_tree));
		*offset += sizeof(t_kd_arr_tree);
		i++;
	}
}

static void		write_indices(
		t_kd_info *kd_info,
		unsigned char *bytes,
		size_t *offset)
{
	int		i;

	ft_memcpy(&bytes[sizeof(cl_int)], &kd_info->indices_num, sizeof(cl_int));
	i = 0;
	while (i < kd_info->indices_num)
	{
		ft_memcpy(&bytes[*offset], &kd_info->indices[i], sizeof(cl_int));
		*offset += sizeof(cl_int);
		i++;
	}
}

void			rt_kd_tree_export(t_kd_info *kd_info, const char *obj_path)
{
	unsigned char	*bytes;
	size_t			offset;
	FILE			*fp;
	size_t			file_size;
	char			*kd_binary_path;

	file_size = sizeof(cl_int) * 2
				+ sizeof(t_kd_arr_tree) * kd_info->nodes_num
				+ sizeof(cl_int) * kd_info->indices_num;
	bytes = rt_safe_malloc(file_size);
	write_nodes(kd_info, bytes, &offset);
	write_indices(kd_info, bytes, &offset);
	kd_binary_path = rt_get_kd_binary_path(obj_path);
	fp = fopen(kd_binary_path, "wb");
	fwrite(bytes, file_size, 1, fp);
	fclose(fp);
	free(bytes);
}
