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
void		rt_add_start_position(int i);

/*
**	Parsing
*/
t_scene		rt_parse_scene(const char *json_scene_file, uint32_t *renderer_flags);
void		parse_json_file(json_t *root, t_tmp *tmp, uint32_t *renderer_flags);
void		count_elements(t_scene *scene, t_tmp *tmp);
void		parse_object(t_tmp *tmp, const char *key, json_t *value, uint32_t *renderer_flags);
void		parse_array(t_tmp *tmp, const char *key, json_t *value, uint32_t *renderer_flags);
void		parse_variable(t_tmp *tmp, const char *key, json_t *value);
void 		parse_string(t_tmp *tmp, const char *key, json_t *value, uint32_t *renderer_flags);
int 		parse_texture(const char *name);
void		init_tmp(t_tmp *tmp);
void		copy_tmp(t_tmp *tmp, t_tmp tmp_source);
int			ft_type_of_structure(const char *param);
int 		ft_type_of_array(int *type_of_element, const char *param, int structure_type);
void 		add_elements(t_scene *scene, t_tmp *tmp);
void 		check_duplicated(bool *checker, int number);
//int 		check_full(t_tmp *tmp);
t_scene		get_hardcoded_scene(); //todo remove after dev
void		rt_correct_scene(t_scene *scene);
void		print_tmp(t_tmp *tmp);
void		print_textures(void);
void		print_scene(t_scene *scene);
int			ft_add_texture_name_back(t_texture_name **list, const char *data);
int 		hex_to_int(const char *temp);


/*
**	Render
*/

void		rt_render(void *rt_ptr, void (*render_func)(void *));
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

void		ft_add_texture_name_back(t_texture_name **list, char *data);

#endif
