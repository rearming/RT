t_material	get_polygon_material(
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		int polygon_index)
{
	return meshes_info[polygons[polygon_index].mesh_index].material;
}
