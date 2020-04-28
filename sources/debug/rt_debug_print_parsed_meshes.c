#include "rt.h"
#include "rt_debug.h"

void		rt_print_parsed_vertices(
		cl_float3 *vertices,
		size_t num_vertices,
		const char *definition)
{
	ft_printf("%s:\n", definition);
	if (!vertices)
		return (void)ft_printf("no such vertices\n\n");
	for (size_t i = 0; i < num_vertices; ++i)
	{
		ft_printf("[%i] ", i + 1);
		rt_print_clfloat3(vertices[i], "");
	}
	ft_printf("\n");
}

void		rt_print_parsed_polygon(t_polygon *polygon)
{
	ft_printf("vertex index: x: [%i], y: [%i], z: [%i]\n",
			polygon->vert_i[0] + 1,
			polygon->vert_i[1] + 1,
			polygon->vert_i[2] + 1);
	ft_printf("normal index: [%i]\n", polygon->vnorm_i + 1);
	ft_printf("texture vertex index: x: [%i], y: [%i], z: [%i]\n",
			polygon->vtex_i[0] == NOT_SET ? -1 : polygon->vtex_i[0] + 1,
			polygon->vtex_i[1] == NOT_SET ? -1 : polygon->vtex_i[1] + 1,
			polygon->vtex_i[2] == NOT_SET ? -1 : polygon->vtex_i[2] + 1);
	ft_printf("mesh index: [%i]\n", polygon->mesh_index);
}

void		rt_print_parsed_polygons(t_polygon *polygons, size_t num_polygons)
{
	size_t		i = 0;

	while (i < num_polygons)
	{
		ft_printf("polygon [%zu]:\n", i);
		rt_print_parsed_polygon(&polygons[i]);
		ft_printf("\n");
		i++;
	}
}

void		rt_print_parsed_meshes(t_meshes *meshes)
{
	rt_print_parsed_vertices(meshes->vertices, meshes->num_vertices, "global vertices");
	rt_print_parsed_vertices(meshes->v_normals, meshes->num_v_normals, "global normals");
	rt_print_parsed_vertices(meshes->v_textures, meshes->num_v_textures, "global texture vertices");
	rt_print_parsed_polygons(meshes->polygons, meshes->num_polygons);
	ft_printf("\n");
}

void		rt_print_parsed_materials(t_meshes *meshes)
{
	for (int i = 0; i < meshes->num_meshes; ++i)
	{
		ft_printf("mesh [%i]\n", i);
		rt_print_material(&meshes->meshes_info[i].material);
		ft_printf("\n");
	}
}
