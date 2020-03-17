#ifndef RT_OPENCL_H
# define RT_OPENCL_H

#include "rt_host_structs.h"

void			rt_opencl_init(void);
void			rt_opencl_render(void *rt_ptr);
void			rt_opencl_prepare_memory(t_rt *rt, uint32_t render_action);
void			rt_opencl_alloc_buffers(uint32_t render_action, t_opencl_mem_obj *memobjs);
void			rt_opencl_release_buffers(uint32_t current_render_action);

void			rt_opencl_handle_error(const char *rt_err_str, int opencl_err_code);

char			*get_opencl_kernel_code_text(size_t *out_size);
void			rt_opencl_create_kernel(const char *compile_options, cl_kernel *out_kernel);
t_render_kernel *rt_get_render_kernel(uint32_t options);

#endif
