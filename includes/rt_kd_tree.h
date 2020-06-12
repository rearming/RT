#ifndef RT_KD_TREE_H
# define RT_KD_TREE_H

# define AXIS_NUM 3
# define X_AXIS 0
# define Y_AXIS 1
# define Z_AXIS 2

# define AABB_OFFSET_EPSILON 0.01f
# define BUCKETS 32
# define EMPTY_COST 1

# define PRINT_INDICES 1

# define KD_TREE_BINARY_EXT "rtkd"

typedef struct			s_split_p
{
	cl_float3			min;
	cl_float3			max;
}						t_split_p;

typedef struct			s_split
{
	cl_float3			arr[2];
	t_split_p			s;
}						t_split;

typedef struct			s_kd_tree
{
	struct s_kd_tree	*left;
	struct s_kd_tree	*right;
	int					left_index;
	int					right_index;
	t_aabb				aabb;
	float				sah;
	float				split;
	int					split_axis;
	t_aabb_objects		objects;
}						t_kd_tree;

t_aabb					*rt_get_all_aabbs(t_meshes *meshes);
t_aabb					get_root_aabb(t_aabb *aabbs, int num_aabbs);
t_kd_tree				*build_kd_tree(t_aabb *all_aabbs, int num_aabbs);
bool					kd_is_obj_in_aabb(t_aabb root_aabb, t_aabb obj_aabb);
t_aabb_objects			kd_get_objects_in_aabb(
		t_aabb aabb,
		t_aabb *all_aabbs,
		t_aabb_objects *prev_objects);
float					kd_get_aabb_area(t_aabb aabb);
t_aabb_objects			get_root_aabb_objects(int num_aabbs);

void					kd_tree_to_list(
		t_kd_tree *tree,
		t_list **out_list,
		int *out_nodes_num);
t_kd_arr_tree			*kd_tree_to_array(
		t_kd_tree *tree,
		int *out_nodes_num,
		int *out_obj_indices_num);
int						kd_tree_count_nodes(t_kd_tree *tree);

void					rt_get_kd_object(
		t_meshes *meshes,
		t_kd_info *out_kd_info);
void					rt_pack_kd_object_indices(t_kd_info *kd_info);
void					free_kd_tree(t_kd_tree *tree, bool free_indices);

void					bzero_kd_info(t_kd_info *out_kd_info);

bool					rt_kd_tree_import(
		t_kd_info *kd_info,
		const char *obj_path);
void					rt_kd_tree_export(
		t_kd_info *kd_info,
		const char *obj_path);
char					*rt_get_kd_binary_path(const char *obj_path);

#endif
