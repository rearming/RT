#include "rt.h"
#include "rt_load_obj_files.h"

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

cl_float3	*rt_get_texture_vertices(const float *raw_vertices, size_t num_vertices)
{
	cl_float3	*vertices;
	size_t		i;

	if (num_vertices < 1)
		return (NULL);
	vertices = rt_safe_malloc(num_vertices * sizeof(cl_float3));
	i = 0;
	while (i < num_vertices)
	{
		vertices[i].x = raw_vertices[2 * i + 0];
		vertices[i].y = raw_vertices[2 * i + 1];
		i++;
	}
	return (vertices);
}

t_polygon		rt_get_polygon(t_raw_obj *raw_obj, int polygon_i)
{
	t_polygon	polygon;

	if (raw_obj->attrib.face_num_verts[polygon_i] != RT_DEFAULT_POLYGON_VERTICES) /// пока только треугольные полигоны
		rt_raise_error("Incorrect number of vertices in polygon!");
	polygon.vert_i[0] = raw_obj->attrib.faces[3 * polygon_i + 0].v_idx;
	polygon.vert_i[1] = raw_obj->attrib.faces[3 * polygon_i + 1].v_idx;
	polygon.vert_i[2] = raw_obj->attrib.faces[3 * polygon_i + 2].v_idx;
	polygon.vnorm_i = raw_obj->attrib.faces[3 * polygon_i + 0].vn_idx; /// пока что 1 треугольник == одна нормаль

	polygon.vtex_i[0] = raw_obj->attrib.faces[3 * polygon_i + 0].vt_idx > 0
			? raw_obj->attrib.faces[3 * polygon_i + 0].vt_idx : NOT_SET;
	polygon.vtex_i[1] = raw_obj->attrib.faces[3 * polygon_i + 1].vt_idx > 0
			? raw_obj->attrib.faces[3 * polygon_i + 1].vt_idx : NOT_SET;
	polygon.vtex_i[2] = raw_obj->attrib.faces[3 * polygon_i + 2].vt_idx > 0
			? raw_obj->attrib.faces[3 * polygon_i + 2].vt_idx : NOT_SET;
	return (polygon);
}

cl_int			get_mesh_index(tinyobj_shape_t *shapes, int num_shapes, int polygon_i)
{
	int		i;

	i = 0;
	while (i < num_shapes)
	{
		if (polygon_i >= (int)shapes[i].face_offset && polygon_i < (int)shapes[i].length + (int)shapes[i].face_offset)
			return (i);
		i++;
	}
	return (0);
}

t_polygon		*rt_get_all_polygons(t_raw_obj *raw_obj)
{
	t_polygon	*polygons;
	size_t		i;

	if (raw_obj->attrib.num_faces < 1)
		return (NULL);
	polygons = rt_safe_malloc(raw_obj->attrib.num_faces / 3 * sizeof(t_polygon));
	i = 0;
	while (i < raw_obj->attrib.num_faces / 3)
	{
		polygons[i] = rt_get_polygon(raw_obj, i);
		polygons[i].mesh_index = get_mesh_index(raw_obj->shapes, raw_obj->num_shapes, i);
		i++;
	}
	return (polygons);
}

t_mesh_info		*rt_get_mesh_info(t_raw_obj *raw_obj)
{
	t_mesh_info		*mesh_info;
	int				i;
	int				material_ids_id;

	if (raw_obj->num_shapes < 1)
		return (NULL);
	mesh_info = rt_safe_malloc(raw_obj->num_shapes * sizeof(t_mesh_info));
	i = 0;
	material_ids_id = 0;
	while (i < raw_obj->num_shapes)
	{
		if (raw_obj->attrib.material_ids[i] == NOT_SET)
			mesh_info[i].material = rt_default_material();
		else
			mesh_info[i].material =
				rt_convert_obj_material(rt_get_obj_material(
						&raw_obj->materials[
								raw_obj->attrib.material_ids[material_ids_id]]));
		material_ids_id += (int)raw_obj->shapes[i].length;
		i++;
	}
	return (mesh_info);
}

void			rt_get_meshes(t_raw_obj *raw_obj, t_meshes *out_meshes)
{
	out_meshes->num_polygons = raw_obj->attrib.num_faces / 3;
	out_meshes->num_vertices = raw_obj->attrib.num_vertices;
	out_meshes->num_v_normals = raw_obj->attrib.num_normals;
	out_meshes->num_v_textures = raw_obj->attrib.num_texcoords;
	out_meshes->num_meshes = raw_obj->num_shapes;
	out_meshes->vertices = rt_get_vertices(raw_obj->attrib.vertices, raw_obj->attrib.num_vertices);
	out_meshes->v_normals = rt_get_vertices(raw_obj->attrib.normals, raw_obj->attrib.num_normals);
	out_meshes->v_textures = rt_get_texture_vertices(raw_obj->attrib.texcoords, raw_obj->attrib.num_texcoords);
	out_meshes->polygons = rt_get_all_polygons(raw_obj);
	out_meshes->meshes_info = rt_get_mesh_info(raw_obj);
}

