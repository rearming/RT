#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "rt.h"
#include "rt_load_obj_files.h"
#include "rt_debug.h"
#include <sys/stat.h>

#define LSTAT_FAIL -1
#define INVALID_BUFF_SIZE 0

static inline size_t	get_buff_size(const char *path)
{
	struct stat		filestruct;

	if (lstat(path, &filestruct) == LSTAT_FAIL)
		return (INVALID_BUFF_SIZE);
	return (filestruct.st_size);
}

static inline char 		*read_obj_file(const char *path_to_obj, size_t *out_size)
{
	char			*buf;
	const size_t	buff_size = get_buff_size(path_to_obj);
	const int		fd = open(path_to_obj, O_RDONLY);

	if (fd < 0 || buff_size == INVALID_BUFF_SIZE)
	{
		fd < 0 ? close(fd) : 0;
		return (NULL);
	}
	buf = rt_safe_malloc(sizeof(char) * (buff_size + 1));
	buf[buff_size] = '\0';
	if (read(fd, buf, buff_size) <= 0)
	{
		free(buf);
		close(fd);
		return (NULL);
	}
	*out_size = buff_size;
	return (buf);
}

static inline bool get_raw_obj(const char *path_to_obj, t_raw_obj *out_raw_obj)
{
	t_raw_obj	raw_obj;
	int			err;
	size_t		size;

	size = 0;
	const char *obj_data = read_obj_file(path_to_obj, &size);
	if (!obj_data)
		return (false);
	err = tinyobj_parse_obj(&raw_obj.attrib, &raw_obj.shapes, (size_t*)&raw_obj.num_shapes,
			&raw_obj.materials, (size_t*)&raw_obj.num_materials, obj_data, size, RT_OBJLOADER_NOFLAGS);
	if (err != TINYOBJ_SUCCESS)
		return (false);
	free((void*)obj_data);
	*out_raw_obj = raw_obj;
	return (true);
}

static void		null_meshes(t_meshes *out_meshes)
{
	out_meshes->num_polygons = 0;
	out_meshes->num_vertices = 0;
	out_meshes->num_v_normals = 0;
	out_meshes->num_v_textures = 0;
	out_meshes->num_meshes = 0;
	out_meshes->meshes_info = NULL;
	out_meshes->polygons = NULL;
	out_meshes->vertices = 0;
	out_meshes->v_normals = NULL;
	out_meshes->v_textures = NULL;
}

bool		rt_load_obj_file(const char *path_to_obj, t_meshes *out_meshes)
{
	t_raw_obj			raw_obj;

	if (!get_raw_obj(path_to_obj, &raw_obj))
	{
		ft_printf_fd(STDERR_FILENO, "[Warning] Can't read .obj file.\n");
		null_meshes(out_meshes);
		return (false);
	}
	rt_get_meshes(&raw_obj, out_meshes);
	rt_free_raw_obj(&raw_obj);
	return (true);
}
