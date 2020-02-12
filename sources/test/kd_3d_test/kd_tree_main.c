#include "test_header.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"

void	free_kd_tree(t_kd_tree *tree)
{
	if (!tree)
		return;
	free_kd_tree(tree->left);
	free_kd_tree(tree->right);
	if (tree->objects.num != NOT_SET)
		free(tree->objects.indices);
	free(tree);
}

t_opencl	g_opencl;
t_sdl		g_sdl;
int			*g_img_data;
t_textures  g_textures;
cl_float3	g_img_data_float[WIN_WIDTH * WIN_HEIGHT];

int			g_max_height;
float		g_empty_cost;

int		get_max_kd_tree_depth(t_kd_tree *tree)
{
	if (!tree)
		return 0;
	return ft_max(get_max_kd_tree_depth(tree->left), get_max_kd_tree_depth(tree->right)) + 1;
}

int		get_kd_tree_nodes_num(t_kd_tree *tree)
{
	if (!tree)
		return 0;
	return get_kd_tree_nodes_num(tree->left) + get_kd_tree_nodes_num(tree->right) + 1;
}

int		main(void)
{
	t_meshes		meshes;
	t_aabb			*obj_aabbs;
	t_kd_tree		*kd_tree;

	clock_t			start;
	clock_t			end;

	start = clock();
	rt_load_obj_files(&meshes);
	end = clock();
	printf(".obj loaded in [%f] sec.\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	obj_aabbs = rt_get_all_aabbs(&meshes);
	end = clock();
	printf("aabbs of polygons got in [%f] sec.\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	kd_tree = build_kd_tree(obj_aabbs, meshes.num_polygons);
	end = clock();
	printf("k-d tree built in [%f] sec.\n", (double)(end - start) / CLOCKS_PER_SEC);

//	print_kd_tree(kd_tree);

//	printf("left tree depth: [%i]\n", get_max_kd_tree_depth(kd_tree->left));
//	printf("right tree depth: [%i]\n", get_max_kd_tree_depth(kd_tree->right));
//	printf("left tree nodes num: [%i]\n", get_kd_tree_nodes_num(kd_tree->left));
//	printf("right tree nodes num: [%i]\n", get_kd_tree_nodes_num(kd_tree->right));

	export_aabbs(kd_tree);

	free_kd_tree(kd_tree);
}
