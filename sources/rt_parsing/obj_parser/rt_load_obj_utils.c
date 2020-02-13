# include "rt_load_obj_files.h"

inline void			rt_free_raw_obj(t_raw_obj *raw_obj)
{
	tinyobj_attrib_free(&raw_obj->attrib);
	if (raw_obj->materials)
		tinyobj_materials_free(raw_obj->materials, raw_obj->num_materials);
	if (raw_obj->shapes)
		tinyobj_shapes_free(raw_obj->shapes, raw_obj->num_shapes);
}
