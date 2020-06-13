/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_load_obj_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by dgreat            #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_load_obj_files.h"

inline void			rt_free_raw_obj(t_raw_obj *raw_obj)
{
	tinyobj_attrib_free(&raw_obj->attrib);
	if (raw_obj->materials)
		tinyobj_materials_free(raw_obj->materials, raw_obj->num_materials);
	if (raw_obj->shapes)
		tinyobj_shapes_free(raw_obj->shapes, raw_obj->num_shapes);
}

inline void			rt_free_meshes(t_meshes *meshes)
{
	if (meshes->polygons)
		free(meshes->polygons);
	if (meshes->meshes_info)
		free(meshes->meshes_info);
	if (meshes->vertices)
		free(meshes->vertices);
	if (meshes->v_normals)
		free(meshes->v_normals);
	if (meshes->v_textures)
		free(meshes->v_textures);
}
