#ifndef RT_OPENCL_H
# define RT_OPENCL_H

#include "rt_host_structs.h"

typedef struct		s_kernel_work_sizes
{
	size_t			materials;
	size_t			textures;
	size_t			skybox;
}					t_kernel_work_sizes;

void			rt_opencl_prepare_memory(t_rt *rt, t_rt_renderer *renderer);
void			rt_opencl_init(void);
void			rt_opencl_render(void *rt_ptr);
void			rt_opencl_move_host_mem_to_kernel(
		t_rt_renderer *renderer,
		int max_memobj_num, ...);

char			*get_opencl_kernel_code_text(const char *kernel_path, size_t *out_size);
void			opencl_clean_memobjs(t_rt_renderer *renderer);
void			rt_opencl_setup_image_buffer(t_rt_renderer *renderer);
void			rt_opencl_handle_error(
		const char *rt_err_str,
		int opencl_err_code);

void			rt_opencl_create_kernel(const char *kernel_path,
							 const char *kernel_name,
							 const char *compile_options,
							 cl_kernel *out_kernel,
							 cl_program *out_program);
t_rt_renderer	*rt_get_renderer(uint32_t flags);

char			*rt_get_kernel_compile_options(uint32_t flags);

t_opencl_mem_obj	rt_check_opencl_memobj(t_opencl_mem_obj mem_obj);
void				rt_wavefront_alloc_buffers(t_rt *rt, int memobj_num, ...);
void				rt_wavefront_setup_buffers(t_rt *rt);
#endif
