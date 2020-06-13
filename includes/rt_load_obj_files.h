/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_load_obj_files.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LOAD_OBJ_FILES_H
# define RT_LOAD_OBJ_FILES_H

# include "tiny_obj_loader_c.h"

typedef struct					s_raw_obj
{
	tinyobj_attrib_t	attrib;
	tinyobj_shape_t		*shapes;
	int					num_shapes;
	tinyobj_material_t	*materials;
	int					num_materials;

}								t_raw_obj;

typedef struct s_meshes			t_meshes;
typedef struct s_obj_material	t_obj_material;
typedef struct s_material		t_material;

t_obj_material					rt_get_obj_material(
		tinyobj_material_t *material);
t_material						rt_convert_obj_material(
		t_obj_material obj_material);
t_material						rt_default_material(void);

void							rt_get_meshes(
		t_raw_obj *raw_obj, t_meshes *out_meshes);
void							rt_free_raw_obj(t_raw_obj *raw_obj);
void							rt_free_meshes(t_meshes *meshes);

void							bzero_meshes(t_meshes *out_meshes);

bool							rt_load_obj_file(
		const char *path_to_obj, t_meshes *out_meshes);

cl_float3						*rt_get_vertices(
		const float *raw_vertices, size_t num_vertices);
cl_float3						*rt_get_texture_vertices(
		const float *raw_vertices, size_t num_vertices);

#endif
