#ifndef KD_2D_TREE_HEADER_H
# define KD_2D_TREE_HEADER_H

# define KD_SCENE_WIDTH 7
# define KD_SCENE_HEIGHT 6
# define KD_SCENE_SIZE (KD_SCENE_WIDTH * KD_SCENE_WIDTH)

# define KD_MAX_OBJ_IN_LEAF 3

# define MIN_OBJ_IN_LEAF 0
# define BUCKETS 32
# define EMPTY_COST 1
// все эти параметры нуждаются в корректировке
// на основе тестов производительности

extern int g_max_height;
extern float g_empty_cost;

# define AXIS_NUM 2
# define X_AXIS 0
# define Y_AXIS 1

# define Z_AXIS 2

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define KD_LEFT 1
# define KD_RIGHT 2

# define SPLIT_NUM 2

typedef struct	s_bounds
{
	cl_float2		min;
	cl_float2		max;
}				t_bounds;

typedef union	u_aabb
{
	cl_float2	arr[2];
	t_bounds	bounds;
}				t_aabb;

typedef struct	s_split_p
{
	cl_float2	min;
	cl_float2	max;
}				t_split_p;

typedef union	u_split
{
	cl_float2	arr[SPLIT_NUM];
	t_split_p	s;
}				t_split;

typedef struct	s_kd_tree t_kd_tree;

typedef struct	s_kd_tree
{
	t_kd_tree	*left;
	t_kd_tree	*right;
	t_aabb		aabb;
	float		sah;
	int			indices[KD_MAX_OBJ_IN_LEAF];
	int			obj_num;
}				t_kd_tree;

t_kd_tree	*build_2d_kd_tree(t_aabb *obj_aabbs, int num_aabbs);
void		start_build_kd_2d_tree(t_aabb *obj_aabbs, int num_aabbs);
void 		test_kd_2d_tree_main(void);

t_aabb		get_2d_root_aabb(t_aabb *obj_aabbs, int num_aabbs);

/*
**	Printing
*/

void		print_cl_float2(cl_float2 vec, const char *definition);
void		print_2d_aabb(t_aabb aabb);
void		print_all_2d_aabbs(t_aabb *aabbs, int num_aabb);
void		kd_2d_print_node(t_kd_tree *node);
void	 	print_2d_kd_traverse(t_kd_tree *root, int level);
void		print_2d_kd_tree(t_kd_tree *root);

/*
**	Drawing
*/

void		graphic_print_kd_tree(t_kd_tree *tree, t_aabb *obj_aabbs, int num_aabbs);
void		kd_2d_draw_loop(t_aabb *obj_aabbs, int num_aabbs);

#endif
