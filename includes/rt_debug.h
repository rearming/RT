#ifndef RT_DEBUG_H
# define RT_DEBUG_H

#include "rt.h"
#include "tiny_obj_loader_c.h"

/*
**	debug
*/

void		rt_print_clfloat3(cl_float3 vec);
void		rt_print_float3_color(cl_float3 color, const char *definition);
void rt_print_debug_info(t_rt *rt, t_rt_renderer *renderer);
void		print_cl_device_info(void);

/*
**	.obj info printing
*/
void		rt_print_obj(tinyobj_attrib_t *attrib, tinyobj_shape_t *shape, size_t num_shapes);
void		rt_print_material(const t_material *material);
void		rt_print_parsed_meshes(t_meshes *meshes);
void		rt_print_mtl_file(tinyobj_material_t *materials, int num_materials);
void		rt_print_parsed_materials(t_meshes *meshes);
/*
**	Profiling
*/

void		rt_pathtrace_profile(t_rt *rt, int max_samples);
void		rt_print_opencl_profile_info(void);

#endif
