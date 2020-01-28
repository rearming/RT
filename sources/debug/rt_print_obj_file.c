#include "rt_debug_utils.h"
#include "rt.h"

void	rt_print_obj_vertex(const float *vertices, unsigned int i, const char *definition)
{
	ft_printf("%13s [%i] (in obj: [%i]): x: [%f] y: [%f] z: [%f]\n",
			definition, i, i + 1,
			vertices[3 * i + 0],
			vertices[3 * i + 1],
			vertices[3 * i + 2]);
}

void	rt_print_obj_faces(tinyobj_attrib_t *attrib)
{
	for (unsigned i = 0; i < attrib->num_faces / 3; ++i)
	{
		ft_printf("face: [%u]\n", i);
		ft_printf("num vertices: [%u]\n", attrib->face_num_verts[i]);
		ft_printf("vertices on face:\n");
		for (int j = 0; j < attrib->face_num_verts[j]; ++j)
		{
			unsigned	vertex = attrib->faces[3 * i + j].v_idx;
			if (vertex < attrib->num_vertices)
				rt_print_obj_vertex(attrib->vertices, vertex, "vertex");
			vertex = attrib->faces[3 * i + j].vn_idx;
			if (vertex < attrib->num_normals)
				rt_print_obj_vertex(attrib->vertices, vertex, "normal vertex");
			vertex = attrib->faces[3 * i + j].vt_idx;
			if (vertex < attrib->num_texcoords)
				rt_print_obj_vertex(attrib->vertices, vertex, "texture vertex");
			ft_printf("\n");
		}
		ft_printf("\n");
	}
}

void	rt_print_obj_attrib(tinyobj_attrib_t *attrib)
{
	ft_printf("num vertices: [%u]\n", attrib->num_vertices);
	ft_printf("num faces: [%u] (real num: [%i])\n", attrib->num_faces, attrib->num_faces / 3);
	for (unsigned i = 0; i < attrib->num_vertices; ++i)
		rt_print_obj_vertex(attrib->vertices, i, "global vertex");
	ft_printf("\n");
	for (unsigned j = 0; j < attrib->num_normals; ++j)
		rt_print_obj_vertex(attrib->normals, j, "global normal vertex");
	ft_printf("\n");
	for (unsigned k = 0; k < attrib->num_texcoords; ++k)
		rt_print_obj_vertex(attrib->texcoords, k, "global texture vertex");
	rt_print_obj_faces(attrib);
}

void	rt_print_obj_shape(tinyobj_shape_t *shape)
{
	ft_printf("name: [%s]\n", shape->name);
	ft_printf("face_offset: [%u]\n", shape->face_offset);
	ft_printf("length: [%u]\n", shape->length);
	ft_printf("\n");
}

//void	rt_print_

void	rt_print_obj(tinyobj_attrib_t *attrib, tinyobj_shape_t *shape, size_t num_shapes)
{
	rt_print_obj_attrib(attrib);
	for (size_t i = 0; i < num_shapes; ++i)
	{
		rt_print_obj_shape(&shape[i]);
	}
}
