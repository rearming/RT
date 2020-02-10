#include "rt.h"
#include "rt_kd_tree.h"

cl_float3	get_min_bounds(cl_float3 vertices[RT_DEFAULT_POLYGON_VERTICES])
{
	cl_float3	min_bounds;

	min_bounds.x = fminf(vertices[0].x, fminf(vertices[1].x, vertices[2].x));
	min_bounds.y = fminf(vertices[0].y, fminf(vertices[1].y, vertices[2].y));
	min_bounds.z = fminf(vertices[0].z, fminf(vertices[1].z, vertices[2].z));
	return (min_bounds);
}

cl_float3	get_max_bounds(cl_float3 vertices[RT_DEFAULT_POLYGON_VERTICES])
{
	cl_float3	max_bounds;

	max_bounds.x = fmaxf(vertices[0].x, fmaxf(vertices[1].x, vertices[2].x));
	max_bounds.y = fmaxf(vertices[0].y, fmaxf(vertices[1].y, vertices[2].y));
	max_bounds.z = fmaxf(vertices[0].z, fmaxf(vertices[1].z, vertices[2].z));
	return (max_bounds);
}

t_aabb		get_aabb_polygon(cl_float3 vertices[RT_DEFAULT_POLYGON_VERTICES])
{
	t_aabb	aabb;

	aabb.bounds.min = get_min_bounds(vertices);
	aabb.bounds.max = get_max_bounds(vertices);
	return (aabb);
}

t_aabb		*rt_get_all_aabbs(t_meshes *meshes)
{
	t_aabb		*tris_aabb;

	tris_aabb = rt_safe_malloc(sizeof(t_aabb) * meshes->num_polygons);
	for (int i = 0; i < meshes->num_polygons; ++i)
	{
		tris_aabb[i] = get_aabb_polygon((cl_float3[RT_DEFAULT_POLYGON_VERTICES]){
			meshes->vertices[meshes->polygons[i].vert_i[0]],
			meshes->vertices[meshes->polygons[i].vert_i[1]],
			meshes->vertices[meshes->polygons[i].vert_i[2]]});
	}
	return (tris_aabb);
}
