#include "test_header.h"
#include "rt_kd_tree.h"

void 	kd_tree_to_list(t_kd_tree *tree, t_list **out_list, int *out_nodes_num)
{
	if (!tree)
		return;
	(*out_nodes_num)++;
	ft_lstaddback(out_list, &tree->aabb, sizeof(t_aabb));
	kd_tree_to_list(tree->left, out_list, out_nodes_num);
	kd_tree_to_list(tree->right, out_list, out_nodes_num);
}

t_aabb	*parse_raw_aabbs(const char *filename, int *out_aabbs_num)
{
	FILE *fp = fopen(filename, "rb");

	fread(out_aabbs_num, sizeof(int), 1, fp);

	unsigned char	*raw_data = malloc(sizeof(t_aabb) * (*out_aabbs_num));

	fread(raw_data, sizeof(t_aabb) * (*out_aabbs_num), 1, fp);

	t_aabb	*parsed_aabbs = malloc(sizeof(t_aabb) * (*out_aabbs_num));

	printf("parsed aabbs num: [%i]\n", *out_aabbs_num);

	for (int i = 0; i < *out_aabbs_num; ++i)
		parsed_aabbs[i] = ((t_aabb*)raw_data)[i];
	return parsed_aabbs;
}

void	write_aabbs_to_file(t_list *aabbs, int aabbs_num)
{
	unsigned char	*bytes = rt_safe_malloc((sizeof(t_aabb) * aabbs_num) + sizeof(int));
	t_list	*tmp = aabbs;
	int		offset = 4;

	memcpy(bytes, &aabbs_num, sizeof(int));
	while (tmp)
	{
		memcpy(&bytes[offset], (t_aabb*)tmp->content, sizeof(t_aabb));
//		print_aabb(*(t_aabb*)tmp->content);
		offset += sizeof(t_aabb);
		tmp = tmp->next;
	}
	FILE *fp = fopen("raw_aabbs_data", "wb");
	fwrite(bytes, (sizeof(t_aabb) * aabbs_num) + sizeof(int), 1, fp);
	fclose(fp);
}

void 	export_aabbs(t_kd_tree *tree)
{
	t_list	*aabbs_list = NULL;
	int		aabbs_num = 0;

	kd_tree_to_list(tree, &aabbs_list, &aabbs_num);
	write_aabbs_to_file(aabbs_list, aabbs_num);

//	int 	out_aabbs_num = 0;
//	t_aabb *parsed_aabbs = parse_raw_aabbs("/Users/sleonard/RT/raw_aabbs_data", &out_aabbs_num);
//	print_all_aabbs(parsed_aabbs, out_aabbs_num);
}
