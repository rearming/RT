#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "rt.h"
#include "rt_load_obj_files.h"
#include "rt_debug.h"

static inline t_raw_obj		rt_get_raw_obj(const char *obj_file_path)
{
	t_raw_obj	raw_obj;
	int			err;
	size_t		size;

	size = 0;
	const char *obj_data = ft_readfile(open(obj_file_path, O_RDONLY), &size);
	if (!obj_data)
		rt_raise_error(ERR_READFILE_OBJ);
	err = tinyobj_parse_obj(&raw_obj.attrib, &raw_obj.shapes, (size_t*)&raw_obj.num_shapes,
			&raw_obj.materials, (size_t*)&raw_obj.num_materials, obj_data, size, RT_OBJLOADER_NOFLAGS);
	if (err != TINYOBJ_SUCCESS)
		rt_raise_error(ERR_OBJLOADER_PARSE_OBJ);
	free((void*)obj_data);
	return (raw_obj);
}

void		rt_load_obj_files(t_meshes *out_meshes)
{
//	const char			*obj_file_path = "./assets/3d_models/cube.obj";
	const char			*obj_file_path = "./assets/3d_models/cube_isosphere_materials.obj";
//	const char			*obj_file_path = "./assets/3d_models/cube_plane_sphere.obj";
//	const char			*obj_file_path = "./assets/3d_models/monk_statue_triangulated.obj";
	t_raw_obj			raw_obj;

	raw_obj = rt_get_raw_obj(obj_file_path);
	rt_get_meshes(&raw_obj, out_meshes);
//	rt_print_obj(&raw_obj.attrib, raw_obj.shapes, raw_obj.num_shapes);
//	rt_print_mtl_file(raw_obj.materials, raw_obj.num_materials);
//	rt_print_parsed_meshes(out_meshes);
//	rt_print_parsed_materials(out_meshes);
	rt_free_raw_obj(&raw_obj);
}
