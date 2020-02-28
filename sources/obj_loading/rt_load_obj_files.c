#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "rt.h"
#include "rt_load_obj_files.h"
#include "rt_debug.h"
#include <sys/stat.h>

#define LSTAT_FAIL -1

static inline size_t	get_buff_size(const char *path)
{
	struct stat		filestruct;

	if (lstat(path, &filestruct) == LSTAT_FAIL)
		rt_raise_error(ERR_READ_OBJ_FILE);
	return (filestruct.st_size);
}

static inline char 		*read_obj_file(const char *path_to_obj, size_t *out_size)
{
	char			*buf;
	const size_t	buff_size = get_buff_size(path_to_obj);
	const int		fd = open(path_to_obj, O_RDONLY);

	if (fd < 0)
		rt_raise_error(ERR_READ_OBJ_FILE);
	buf = rt_safe_malloc(sizeof(char) * (buff_size + 1));
	buf[buff_size] = '\0';
	if (read(fd, buf, buff_size) <= 0)
		rt_raise_error(ERR_READ_OBJ_FILE);
	*out_size = buff_size;
	return (buf);
}

static inline t_raw_obj		get_raw_obj(const char *path_to_obj)
{
	t_raw_obj	raw_obj;
	int			err;
	size_t		size;

	size = 0;
	const char *obj_data = read_obj_file(path_to_obj, &size);
	if (!obj_data)
		rt_raise_error(ERR_READ_OBJ_FILE);
	err = tinyobj_parse_obj(&raw_obj.attrib, &raw_obj.shapes, (size_t*)&raw_obj.num_shapes,
			&raw_obj.materials, (size_t*)&raw_obj.num_materials, obj_data, size, RT_OBJLOADER_NOFLAGS);
	if (err != TINYOBJ_SUCCESS)
		rt_raise_error(ERR_OBJLOADER_PARSE_OBJ);
	free((void*)obj_data);
	return (raw_obj);
}

void					rt_load_obj_file(const char *path_to_obj, t_meshes *out_meshes)
{
	const char			*hardcoded_path = "./assets/3d_models/cube.obj";
//	const char			*hardcoded_path = "./assets/3d_models/two_cubes.obj";
//	const char			*hardcoded_path = "./assets/3d_models/isosphere.obj";
//	const char			*hardcoded_path = "./assets/3d_models/sauron_tower.obj";
//	const char			*hardcoded_path = "./assets/3d_models/monk_statue_triangulated.obj";
//	const char			*hardcoded_path = "./assets/3d_models/column.obj";
//	const char			*hardcoded_path = "./assets/3d_models/monkey.obj";
//	const char			*hardcoded_path = "./assets/3d_models/dragon.obj";
//	const char			*hardcoded_path = "./assets/3d_models/one_triangle.obj";
//	const char			*hardcoded_path = "./assets/3d_models/pyramid_cube.obj";
//	const char			*hardcoded_path = "./assets/3d_models/cube_isosphere_materials.obj";
//	const char			*hardcoded_path = "./assets/3d_models/teapot_cornell_box_scene.obj";
//	const char			*hardcoded_path = "./assets/3d_models/test_scene_materials.obj";
//	const char			*hardcoded_path = "./assets/3d_models/cube_plane_sphere.obj";
	t_raw_obj			raw_obj;

	raw_obj = get_raw_obj(path_to_obj ? path_to_obj : hardcoded_path);
	rt_get_meshes(&raw_obj, out_meshes);
#ifdef DEBUG_PRINT_MESHES
//	rt_print_obj(&raw_obj.attrib, raw_obj.shapes, raw_obj.num_shapes);
//	rt_print_mtl_file(raw_obj.materials, raw_obj.num_materials);
	rt_print_parsed_meshes(out_meshes);
	rt_print_parsed_materials(out_meshes);
#endif
	rt_free_raw_obj(&raw_obj);
}
