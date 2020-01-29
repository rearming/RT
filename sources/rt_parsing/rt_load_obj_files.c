#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tiny_obj_loader_c.h"
#include "rt.h"
#include "../debug/rt_debug_utils.h"

cl_float3	*rt_get_vertices(const float *raw_vertices, size_t num_vertices)
{
	cl_float3	*vertices;
	size_t		i;

	if (num_vertices < 1)
		return (NULL);
	vertices = rt_safe_malloc(num_vertices * sizeof(cl_float3));
	i = 0;
	while (i < num_vertices)
	{
		vertices[i].x = raw_vertices[3 * i + 0];
		vertices[i].y = raw_vertices[3 * i + 1];
		vertices[i].z = raw_vertices[3 * i + 2];
		i++;
	}
	return (vertices);
}

t_polygon	rt_get_polygon(const tinyobj_attrib_t *attrib, int polygon_i)
{
	t_polygon	polygon;

	if (attrib->face_num_verts[polygon_i] != RT_DEFAULT_POLYGON_VERTICES) /// пока только треугольные полигоны
		rt_raise_error("Incorrect number of vertices in polygon!");
	polygon.vert_i[0] = attrib->faces[3 * polygon_i + 0].v_idx;
	polygon.vert_i[1] = attrib->faces[3 * polygon_i + 1].v_idx;
	polygon.vert_i[2] = attrib->faces[3 * polygon_i + 2].v_idx;
	polygon.vnorm_i = attrib->faces[3 * polygon_i + 0].vn_idx; /// пока что 1 треугольник == одна нормаль

	polygon.vtex_i[0] = attrib->faces[3 * polygon_i + 0].vt_idx > 0 ? attrib->faces[3 * polygon_i + 0].vt_idx : NOT_SET;
	polygon.vtex_i[1] = attrib->faces[3 * polygon_i + 1].vt_idx > 0 ? attrib->faces[3 * polygon_i + 1].vt_idx : NOT_SET;
	polygon.vtex_i[2] = attrib->faces[3 * polygon_i + 2].vt_idx > 0 ? attrib->faces[3 * polygon_i + 2].vt_idx : NOT_SET;
	polygon.material = (t_material){.albedo = get_float3_color(COL_GREY), .specular = 0}; /// пока что хардкод материала
	return (polygon);
}

t_polygon	*rt_get_all_polygons(const tinyobj_attrib_t *attrib)
{
	t_polygon	*polygons;
	size_t		i;

	polygons = rt_safe_malloc(attrib->num_faces / 3 * sizeof(t_polygon));
	i = 0;
	while (i < attrib->num_faces / 3)
	{
		polygons[i] = rt_get_polygon(attrib, i);
		i++;
	}
	return (polygons);
}

void		rt_get_meshes(const tinyobj_attrib_t *attrib, t_meshes *out_meshes)
{
	out_meshes->num_polygons = attrib->num_faces / 3;
	out_meshes->num_vertices = attrib->num_vertices;
	out_meshes->num_v_normals = attrib->num_normals;
	out_meshes->num_v_textures = attrib->num_texcoords;
	out_meshes->vertices = rt_get_vertices(attrib->vertices, attrib->num_vertices);
	out_meshes->v_normals = rt_get_vertices(attrib->normals, attrib->num_normals);
	out_meshes->v_textures = rt_get_vertices(attrib->texcoords, attrib->num_texcoords);
	out_meshes->polygons = rt_get_all_polygons(attrib);
}

void		rt_load_obj_files(t_meshes *out_meshes)
{
//	const char			*filename = "/Users/sleonard/RT/assets/3d_models/cube.obj";
	const char			*filename = "/Users/sleonard/RT/assets/3d_models/cube_plane_sphere.obj";
//	const char			*filename = "/Users/sleonard/RT/assets/3d_models/monk_statue_triangulated.obj";
	tinyobj_attrib_t	*attrib;
	tinyobj_shape_t		*shapes;
	size_t				num_shapes;
	tinyobj_material_t	*materials;
	size_t				num_materials;
	int					err;

	size_t		size = 0;
	const char *obj_data = ft_readfile(open(filename, O_RDONLY), &size);
	if (!obj_data)
		rt_raise_error(ERR_READFILE_OBJ);
	attrib = rt_safe_malloc(sizeof(tinyobj_attrib_t));
	tinyobj_attrib_init(attrib);
	err = tinyobj_parse_obj(attrib, &shapes, &num_shapes,
			&materials, &num_materials, obj_data, size, RT_OBJLOADER_NOFLAGS);
	free((void*)obj_data);
	if (err != TINYOBJ_SUCCESS)
		rt_raise_error(ERR_OBJLOADER_PARSE_OBJ);
//	rt_print_obj(attrib, shapes, num_shapes);
	rt_get_meshes(attrib, out_meshes);
//	rt_print_parsed_meshes(out_meshes);
	tinyobj_attrib_free(attrib);
	tinyobj_shapes_free(shapes, num_shapes);
	free(attrib);
}
