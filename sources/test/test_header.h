#ifndef TEST_HEADER_H
# define TEST_HEADER_H

#include "rt.h"
#include "rt_debug.h"
#include <time.h>

//#define VERBOSE 1

t_point		*test_get_point_arr(int arr_size);
int			*test_get_int_arr(int arr_size);
void		test_run_kernels(t_rt *rt);
void		test_rt_loop(t_rt *rt);
void		fill_all_g_img_data(t_rt *rt);
double		*test_get_double_arr(int arr_size);

void		rt_test_opencl(void);

double		lerp_avg(double *test_arr, int arr_size);

void 		test_kd_2d_tree_main(void);
void 		test_run_kd_2d_tree(void);
void		test_build_kd_tree(void);

bool		assert_float_equals(float expected, float actual);
bool		assert_int_equals(int expected, int actual);

void		kd_run_traverse_tests(t_kd_tree *tree);

#endif
