#ifndef TEST_KD_TREE_HEADER_H
# define TEST_KD_TREE_HEADER_H

#define WIDTH 6
#define HEIGHT 6

#define MAX_HEIGHT 2

typedef struct	s_kd_obj
{
	cl_float2	pos;
	cl_float2	bounds[4];
	int			index;
}				t_kd_obj;

typedef struct	s_kd_tree t_kd_tree;

typedef struct	s_kd_tree
{
	cl_float2	bounds[4];
	t_kd_tree	*right;
	t_kd_tree	*left;
}				t_kd_tree;

extern t_kd_obj		g_test_kd_scene[HEIGHT][WIDTH];

void		kd_fill_positions(void);
void		kd_print_scene(void);

void		build_kd_tree(t_kd_tree **tree, int level);

#endif
