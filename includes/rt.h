#ifndef RT_H
# define RT_H

# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <dirent.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <fcntl.h>

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include "libft.h"
# include "rt_shared_structs.h"
# include "rt_host_structs.h"
# include "rt_errors.h"
# include "rt_opencl_params_defines.h"
# include "rt_defines.h"
# include "jansson.h"
# include "rt_parser_defines.h"


/*
**	Global pointers
*/

typedef struct s_gui t_gui;

extern t_opencl		g_opencl;
extern t_sdl		g_sdl;
extern t_gui		g_gui;
extern int			*g_img_data;
extern t_textures   g_textures;

/*
**	Init
*/

void		rt_init(t_rt *out_rt, const char *json_scene_file);
void		rt_init_render_params(t_render_params *out_opencl_params, t_cl_info clInfo);
int			init_basic_textures_parameters(void);
void		rt_add_start_position(int i);
char 		*found_file_in_the_folder(const char *file);

/*
**	Render
*/

void		rt_render(void *rt_ptr, void (*render_func)(void *));
void		rt_update_render_params(t_render_kernel *render_kernel,
							 t_render_params *params,
							 uint32_t render_options,
							 uint32_t render_action);
/*
**	Event handling
*/

void		handle_event(t_rt *rt, SDL_Event *events, int events_num);

void		rt_unset_bit(uint32_t *bitfield, uint32_t target);
void		rt_set_bit(unsigned int *bitfield, uint32_t new_param);
void		rt_set_render_algo(uint32_t *old_params, uint32_t new_algo);
bool		rt_bit_isset(uint32_t params, uint32_t target);
void		rt_switch_bit(uint32_t *bitfield, uint32_t target);

/*
**	SDL utils
*/

void		rt_sdl_init(void);
void		rt_textures_init();
void 		rt_skybox_init(void);

/*
**	Utils
*/

void		rt_loop(t_rt *rt);

void		print_cl_build_program_debug(cl_program program);
void		rt_raise_error(const char *err_str);
void		*rt_safe_malloc(size_t size);
bool		rt_exit_clean(void);
bool		rt_camera_moved(t_camera *camera);

#endif
