#ifndef TEST_KD_TREE_HEADER_H
# define TEST_KD_TREE_HEADER_H

# define KD_SCENE_WIDTH 7
# define KD_SCENE_HEIGHT 6
# define KD_SCENE_SIZE (KD_SCENE_WIDTH * KD_SCENE_WIDTH)

# define MAX_OBJ_IN_LEAF 3

# define MIN_OBJ_IN_LEAF 0
# define BUCKETS 32
# define EMPTY_COST 1
// все эти параметры нуждаются в корректировке
// на основе тестов производительности

extern int g_max_height;

# define AXIS 2
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
# define BOUNDS_NUM 4

typedef struct	s_bounds_n
{
	cl_float2	bound0;
	cl_float2	bound1;
	cl_float2	bound2;
	cl_float2	bound3;
}				t_bounds_n;

typedef union	u_bounds
{
	cl_float2	b[BOUNDS_NUM];
	t_bounds_n	n;
}				t_bounds;

typedef struct	s_split_n
{
	cl_float2	split0;
	cl_float2	split1;
}				t_split_n;

typedef union	u_split
{
	cl_float2	s[SPLIT_NUM];
	t_split_n	n;
}				t_split;

typedef struct	s_kd_obj
{
	cl_float2	pos;
	t_bounds 	bounds;
	int			index;
}				t_kd_obj;

typedef struct	s_kd_tree t_kd_tree;

typedef struct	s_kd_tree
{
	t_kd_tree	*left;
	t_kd_tree	*right;
	t_bounds	bounds;
	float		sah;
	int			indices[MAX_OBJ_IN_LEAF];
	int			obj_num;
}				t_kd_tree;

extern t_kd_obj		g_test_kd_scene[KD_SCENE_HEIGHT][KD_SCENE_WIDTH];

void		print_cl_float2(cl_float2 vec);

void		kd_fill_positions(void);
void		kd_print_scene(void);
void		kd_print_node(t_kd_tree *node);
void		print_kd_tree(t_kd_tree *root);

int			kd_get_split_axis(t_bounds bounds);
float		get_surface_area(t_bounds bounds);

int			kd_count_obj_in_bounds(t_kd_obj *objs, t_bounds box_bounds, int out_indices[MAX_OBJ_IN_LEAF]);
void		build_kd_tree(t_kd_tree *tree, t_kd_obj *objects, int level);
void		start_build_kd_tree(t_kd_obj *objects);

void		kd_print_bounds(t_bounds bounds);
void		graphic_print_kd_tree(t_kd_tree *tree, t_kd_obj *objects);

void kd_draw_loop(t_kd_obj *objects);

#endif
