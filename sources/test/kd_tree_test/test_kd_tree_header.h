#ifndef TEST_KD_TREE_HEADER_H
# define TEST_KD_TREE_HEADER_H

# define WIDTH 7
# define HEIGHT 6

# define X_AXIS 0
# define Y_AXIS 1
# define Z_AXIS 2

# define MAX_HEIGHT 2

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
	t_kd_tree	*right;
	t_kd_tree	*left;
	t_bounds	bounds;
	int			obj_num;
}				t_kd_tree;

extern t_kd_obj		g_test_kd_scene[HEIGHT][WIDTH];

void		print_cl_float2(cl_float2 vec);

void		kd_fill_positions(void);
void		kd_print_scene(void);
void		kd_print_node(t_kd_tree *node);
void		print_kd_tree(t_kd_tree *root, int level);

void		build_kd_tree(t_kd_tree **tree, t_bounds bounds, int level);
int			kd_get_split_axis(t_bounds bounds);

#endif
