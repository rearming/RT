#ifndef TEST_HEADER_H
# define TEST_HEADER_H

#include "rt.h"

t_point		*test_get_point_arr(int arr_size);
int			*test_get_int_arr(int arr_size);
void		test_run_kernels(t_rt *rt);
void		test_rt_loop(t_rt *rt);
void		dummy_render_func(t_rt *rt);

#endif
