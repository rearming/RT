/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_opencl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OPENCL_H
# define RT_OPENCL_H

# include "rt_host_structs.h"

void				rt_opencl_init(void);
void				rt_opencl_render(void *rt_ptr);
void				rt_opencl_prepare_memory(t_rt *rt, uint32_t render_action);
void				rt_opencl_alloc_buffers(uint32_t render_action,
		t_opencl_mem_obj *memobjs);
void				rt_opencl_release_buffers(uint32_t current_render_action);

void				rt_opencl_handle_error(const char *rt_err_str,
		int opencl_err_code);

char				*get_opencl_kernel_code_text(const char *kernel_path,
		size_t *out_size);
void				rt_opencl_compile_kernel(const char *kernel_path,
		const char *kernel_name,
		const char *compile_options,
		cl_kernel *out_kernel);
cl_program			rt_get_cached_cl_program(
		const char *kernel_path,
		const char *kernel_name,
		const char *compile_options);

t_render_kernel		*rt_get_render_kernel(uint32_t options);
char				*rt_get_kernel_compile_options(
		uint32_t options, bool includes_only);
void				rt_opencl_compile_kernels(uint32_t render_options);
void				rt_set_kernel_args(cl_kernel kernel, int args_num, ...);

void				set_render_kernel_args(t_render_kernel *render_kernel);
int					switch_img_buffers(int *in_buffer, int *out_buffer);

t_opencl_mem_obj	rt_check_opencl_memobj(t_opencl_mem_obj mem_obj);
void				rt_opencl_prepare_mem_arr1(t_rt *rt,
		t_opencl_mem_obj *mem_obj);
void				rt_opencl_prepare_mem_arr2(t_rt *rt,
		t_opencl_mem_obj *mem_obj);
void				rt_opencl_prepare_mem_arr3(t_rt *rt,
		t_opencl_mem_obj *mem_obj);
void				rt_opencl_prepare_mem_arr4(t_rt *rt,
		t_opencl_mem_obj *mem_obj);
void				rt_opencl_prepare_mem_arr5(t_rt *rt,
		t_opencl_mem_obj *mem_obj);

/*
**	kernels execution
*/

void				exec_render_kernel(t_rt *rt, t_render_kernel *render_kernel,
		const size_t *work_size);
void				exec_depth_of_field_kernel(t_rt *rt, cl_kernel kernel,
		const size_t *work_size);
void				exec_sepia_kernel(t_rt *rt, cl_kernel kernel,
		const size_t *work_size);
void				exec_cartoon_kernel(t_rt *rt, cl_kernel kernel,
		const size_t *work_size);

typedef struct		s_kernel_info
{
	char			*kernel_name;
	char			*kernel_path;
}					t_kernel_info;

#endif
