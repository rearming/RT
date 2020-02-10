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

extern t_opencl		g_opencl;
extern t_sdl		g_sdl;
extern int			*g_img_data;
extern cl_float3	g_img_data_float[WIN_WIDTH * WIN_HEIGHT];
extern t_textures   g_textures;

/*
**	Init
*/

void		rt_init(t_rt *out_rt, const char *json_scene_file);
void		rt_init_renderer_params(t_renderer_params *out_opencl_params);
int			init_basic_textures_parameters(void);
void		init_final_texture_parameters(size_t list_size);
void		rt_add_start_position(int i);

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
void		rt_update_renderer_params(t_rt *rt, t_rt_renderer *renderer);

/*
**	Event handling
*/

void		handle_event(SDL_Event *event, t_rt *rt);

void		rt_unset_render_params(uint32_t *old_params, uint32_t target);
void		rt_set_render_params(unsigned int *old_params, uint32_t new_param);
void		rt_set_render_algo(uint32_t *old_params, uint32_t new_algo);
bool		rt_params_isset(uint32_t params, uint32_t target);
void		rt_switch_render_param(uint32_t *params, uint32_t target);

/*
**	SDL utils
*/

void		rt_sdl_init(void);
void		rt_textures_init();

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
