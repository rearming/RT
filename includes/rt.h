#ifndef RT_H
# define RT_H

# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
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

extern t_opencl	g_opencl;
extern t_sdl	g_sdl;
extern int		*g_img_data;

/*
**	Init
*/

void		rt_init(t_rt *out_rt, const char *json_scene_file);

/*
**	Parsing
*/

t_scene		rt_parse_scene(const char *json_scene_file);
t_scene		get_hardcoded_scene(); //todo remove after dev

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

void		rt_opencl_init(void);
void		rt_opencl_render(t_rt *rt);
void		rt_opencl_copy_host_mem_to_kernel(int kernel_mem_object_nbr, ...);
char		*get_opencl_kernel_code_text(size_t *out_size);
void		opencl_clean_memobjs(void);
void		rt_opencl_setup_image_buffer(void);
/*
**	Utils
*/

void		rt_loop(t_rt *rt);

void		print_cl_build_program_debug(void);
void		rt_raise_error(int err_code);
void		*rt_safe_malloc(size_t size);
t_bool		rt_exit_clean(void);

#endif
