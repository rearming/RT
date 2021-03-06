#include "rt_load_obj_files.h"
#include "test_header.h"
#include "rt_parsing.h"
#include "rt_kd_tree.h"

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

void	kd_check_indices(t_kd_tree *tree, int *indices)
{
	if (!tree)
		return;
	kd_check_indices(tree->left, indices);
	kd_check_indices(tree->right, indices);

	for (int i = 0; i < tree->objects.num; ++i)
		indices[tree->objects.indices[i]] = true;
}

void	run_check_indices(t_kd_tree *tree)
{
	int 	*indices = malloc(sizeof(int) * 100);
	for (int i = 0; i < 100; ++i)
		indices[i] = NOT_SET;
	kd_check_indices(tree, indices);
	int count = 0;
	for (int j = 0; j < 100; ++j)
	{
		if (indices[j] == true)
			count++;
	}
	ft_printf("count: [%i]\n", count);
}

int		main(int argc, char **argv)
{
	t_meshes		meshes;
	t_aabb			*all_aabbs;
	t_kd_tree		*kd_tree;

	clock_t			start;
	clock_t			end;

	start = clock();
	rt_load_obj_file(argc < 2 ? NULL : argv[1], &meshes);
	end = clock();
	printf(".obj loaded in [%f] sec.\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	all_aabbs = rt_get_all_aabbs(&meshes);
	end = clock();
	printf("aabbs of polygons got in [%f] sec.\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	kd_tree = build_kd_tree(all_aabbs, meshes.num_polygons);
	end = clock();
	printf("k-d tree built in [%f] sec.\n", (double)(end - start) / CLOCKS_PER_SEC);

//	print_kd_tree(kd_tree);

//	printf("left tree depth: [%i]\n", get_max_kd_tree_depth(kd_tree->left));
//	printf("right tree depth: [%i]\n", get_max_kd_tree_depth(kd_tree->right));
//	printf("left tree nodes num: [%i]\n", kd_tree_count_nodes(kd_tree->left));
//	printf("right tree nodes num: [%i]\n", kd_tree_count_nodes(kd_tree->right));

	export_aabbs(kd_tree);

//	t_kd_arr_tree	*kd_tree_arr = kd_tree_to_array(kd_tree);

//	printf("\nprinting kd-tree array:\n");
//	print_kd_tree_arr(kd_tree_arr, 0);

//	kd_run_traverse_tests(kd_tree_arr);
//	print_kd_node(kd_tree->left);

//	free(kd_tree_arr);

	free(all_aabbs);
	free_kd_tree(kd_tree, 0);
	rt_free_meshes(&meshes);
}
