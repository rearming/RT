#ifndef RT_H
# define RT_H

# define STB_IMAGE_IMPLEMENTATION
# define STB_IMAGE_RESIZE_IMPLEMENTATION

# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <dirent.h>
# include <SDL.h>

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include "libft.h"
# include "rt_structs.h"
# include "rt_errors.h"
# include "rt_defines.h"

/*
**	Global pointers
*/

extern t_opencl	    g_opencl;
extern t_sdl	    g_sdl;
extern int		    *g_img_data;
extern t_textures   g_textures;

/*
**	Init
*/

void		rt_init(t_rt *out_rt, const char *json_scene_file);
void 		init_basic_textures_parameters(void);
void		rt_add_start_position(int i);
/*
**	Parsing
*/

t_scene		rt_parse_scene(const char *json_scene_file);
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
void		rt_textures_init();

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
t_bool		rt_exit_clean(void);

/*
**	Math utils
*/

cl_float3	rt_degree_to_rad(cl_float3 rotation_degrees);
t_bool		rt_clfloat3_equals(cl_float3 a, cl_float3 b);

cl_float3	get_float3_color(int hex_color);

#endif
