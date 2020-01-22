#ifndef RT_DEBUG_UTILS_H
# define RT_DEBUG_UTILS_H


/*
**	debug
*/

void		print_clfloat3(cl_float3 vec);
void		rt_print_debug_info(t_rt *rt);
void		print_cl_device_info(void);

/*
**	Profiling
*/

void		rt_pathtrace_profile(t_rt *rt, int max_samples);

#endif
