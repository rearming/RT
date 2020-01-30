#ifndef RT_LOAD_OBJ_FILES_H
# define RT_LOAD_OBJ_FILES_H

# define TINYOBJ_LOADER_C_IMPLEMENTATION
# include "tiny_obj_loader_c.h"

typedef struct			s_raw_obj
{
	tinyobj_attrib_t	*attrib;
	tinyobj_shape_t		*shapes;
	size_t				num_shapes;
	tinyobj_material_t	*materials;
	size_t				num_materials;

}						t_raw_obj;

#endif
