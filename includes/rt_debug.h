#ifndef RT_DEBUG_H
# define RT_DEBUG_H

#include "rt.h"
#include "tiny_obj_loader_c.h"

/*
**	debug
*/

void		rt_print_clfloat3(cl_float3 vec, const char *definition);
void		rt_print_float3_color(cl_float3 color, const char *definition);
void		rt_print_debug_info(t_rt *rt, t_rt_renderer *renderer);
void		print_cl_device_info(void);

/*
**	.obj info printing
*/

void		rt_print_obj(tinyobj_attrib_t *attrib, tinyobj_shape_t *shape, size_t num_shapes);
void		rt_print_material(const t_material *material);
void		rt_print_parsed_meshes(t_meshes *meshes);
void		rt_print_mtl_file(tinyobj_material_t *materials, int num_materials);

/*
**	Profiling
*/

void		rt_pathtrace_profile(t_rt *rt, int max_samples);
void		rt_print_opencl_profile_info(void);

/*
**	Objects
*/

void		rt_print_parsed_materials(t_meshes *meshes);
void		rt_print_sphere(t_object *sphere);
void		rt_print_parsed_polygon(t_polygon *polygon);

/*
** k-d tree
*/

typedef struct s_kd_tree		t_kd_tree;
typedef struct s_kd_arr_node	t_kd_arr_tree;
typedef struct s_aabb			t_aabb;

void		print_kd_tree_arr(t_kd_arr_tree *tree_arr, int index);
void		print_kd_tree(t_kd_tree *tree);
void		print_kd_node(t_kd_tree *node);
void		print_aabb(t_aabb aabb);
void		print_all_aabbs(t_aabb *aabbs, int num_aabb);

void		export_aabbs(t_kd_tree *tree);

#endif
