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

cl_float3	*rt_get_texture_vertices(
		const float *raw_vertices,
		size_t num_vertices)
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
