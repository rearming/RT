#ifndef RT_KD_TREE_H
# define RT_KD_TREE_H

# define AXIS_NUM 3
# define X_AXIS 0
# define Y_AXIS 1
# define Z_AXIS 2

# define KD_MAX_OBJ_IN_LEAF 3

# define MIN_OBJ_IN_LEAF 0
# define BUCKETS 32
# define EMPTY_COST 0.5

# define KD_MAX_HEIGHT 23 // ~log2(10kk)

#define PRINT_INDICES 1

typedef struct		s_bounds
{
	cl_float3		min;
	cl_float3		max;
}					t_bounds;

typedef union		u_aabb
{
	cl_float3		arr[2];
	t_bounds		bounds;
}					t_aabb;

typedef struct		s_split_p
{
	cl_float3		min;
	cl_float3		max;
}					t_split_p;

typedef struct		s_split
{
	cl_float3		arr[2];
	t_split_p		s;
}					t_split;

typedef struct		s_aabb_objects
{
	int				num;
	int				*indices;
}					t_aabb_objects;

typedef struct s_kd_tree	t_kd_tree;

typedef struct		s_kd_tree
{
	t_kd_tree		*left;
	t_kd_tree		*right;
	t_aabb			aabb;
	float			sah;
	t_aabb_objects	objects;
}					t_kd_tree;

t_aabb		*rt_get_all_aabbs(t_meshes *meshes);
t_aabb		get_root_aabb(t_aabb *aabbs, int num_aabbs);
t_kd_tree	*build_kd_tree(t_aabb *all_aabbs, int num_aabbs);

#endif
