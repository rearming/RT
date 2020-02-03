#ifndef RT_H
# define RT_H

# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <SDL.h>
# include <fcntl.h>

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include "libft.h"
# include "rt_structs.h"
# include "rt_errors.h"
# include "rt_defines.h"
# include "jansson.h"
# include "rt_parser_defines.h"
/*
**	Global pointers
*/

extern t_opencl		g_opencl;
extern t_sdl		g_sdl;
extern int			*g_img_data;
extern cl_float3	g_img_data_float[WIN_WIDTH * WIN_HEIGHT];

/*
**	Init
*/

void		rt_init(t_rt *out_rt, const char *json_scene_file);

/*
**	Parsing
*/
t_scene		rt_parse_scene(const char *json_scene_file);
void		init_tmp(t_tmp *tmp);
int			ft_check_if_exist(int checker, int type);
void		parse_elements(json_t *root, t_tmp *tmp);
char		*read_file(const char *argv, int buff_size);
int			type_of_json_array(const char *param, int type);
int			type_of_object(const char *param, int type);
int			type_of_structure_object(const char *param);
int			type_of_variable(const char *param, int type);
void		add_array(cl_float3 *elem, json_t *value);
void 		add_elements(t_scene *scene, t_tmp *tmp);
t_scene		get_hardcoded_scene(); //todo remove after dev
void		rt_correct_scene(t_scene *scene);

/*
**	Render
*/

void		rt_render(t_rt *rt, void (*render_func)(t_rt *));

/*
**	Event handling
*/

void		handle_event(SDL_Event *event, t_rt *rt);

/*
**	SDL utils
*/

void		rt_sdl_init(void);

/*
**	OpenCL utils
*/

void cl_set_kernel(t_rt *rt, int mode);

char		*concat_opencl_kernel_code(int files_nbr, ...);
void		rt_opencl_init(void);
void		rt_opencl_render(t_rt *rt);
void		rt_opencl_move_host_mem_to_kernel(int kernel_mem_object_nbr, ...);
char		*get_opencl_kernel_code_text(size_t *out_size);
void		opencl_clean_memobjs(void);
void		rt_opencl_setup_image_buffer(void);
void		rt_opencl_handle_error(int rt_err_code, int opencl_err_code);

/*
**	Utils
*/

void		rt_loop(t_rt *rt);

void		print_cl_build_program_debug(void);
void		rt_raise_error(int err_code);
void		*rt_safe_malloc(size_t size);
bool		rt_exit_clean(void);

/*
**	Math utils
*/

cl_float3	rt_degree_to_rad(cl_float3 rotation_degrees);
bool		rt_float3_equals(cl_float3 a, cl_float3 b);
cl_float3	mul_float3(cl_float3 vec, float mul);

cl_float3	get_float3_color(int hex_color);

#endif
