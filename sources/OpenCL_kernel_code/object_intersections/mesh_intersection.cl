int		ray_mesh_intersect(
		__constant t_meshes *mesh_info,
		__constant t_polygon *polygons,
		__constant float3 *vertices,
		__constant float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit)
{
	int		closest_polygon_index = NOT_SET;

	for (int i = 0; i < mesh_info->num_polygons; i++)
	{
		if (ray_triangle_intersect_MT_polygon(
				vertices[polygons[i].vert_i[0]],
				vertices[polygons[i].vert_i[1]],
				vertices[polygons[i].vert_i[2]],
				v_normals[polygons[i].vnorm_i],
				0, 0, 0, /// текстурных вертексов пока нет
				ray, out_best_hit))
			closest_polygon_index = i;
	}
	return (closest_polygon_index);
}
