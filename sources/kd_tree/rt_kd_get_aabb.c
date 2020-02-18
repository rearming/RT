#include "rt.h"
#include "rt_kd_tree.h"
#include "rt_math_utils.h"

t_aabb		get_aabb_polygon(cl_float3 vertices[RT_DEFAULT_POLYGON_VERTICES])
{
	t_aabb	aabb;

	aabb.bounds.min = fmin_float3(vertices[0], fmin_float3(vertices[1], vertices[2]));
	aabb.bounds.max = fmax_float3(vertices[0], fmax_float3(vertices[1], vertices[2]));
	return (aabb);
}

t_aabb		get_root_aabb(t_aabb *aabbs, int num_aabbs)
{
	t_aabb	root_aabb;
	int		i = 0;

	root_aabb.bounds.min = (cl_float3){{INFINITY, INFINITY, INFINITY}};
	root_aabb.bounds.max = (cl_float3){{-INFINITY, -INFINITY, -INFINITY}};
	while (i < num_aabbs)
	{
		root_aabb.bounds.min = fmin_float3(root_aabb.bounds.min, aabbs[i].bounds.min);
		root_aabb.bounds.max = fmax_float3(root_aabb.bounds.max, aabbs[i].bounds.max);
		i++;
	}
	return (root_aabb);
}

t_aabb		*rt_get_all_aabbs(t_meshes *meshes)
{
	t_aabb		*tris_aabb;
	int			i;

	tris_aabb = rt_safe_malloc(sizeof(t_aabb) * meshes->num_polygons);
	i = 0;
	while (i < meshes->num_polygons)
	{
		tris_aabb[i] = get_aabb_polygon((cl_float3[RT_DEFAULT_POLYGON_VERTICES]){
			meshes->vertices[meshes->polygons[i].vert_i[0]],
			meshes->vertices[meshes->polygons[i].vert_i[1]],
			meshes->vertices[meshes->polygons[i].vert_i[2]]});
		i++;
	}
	return (tris_aabb);
}
