
bool		get_hit_material(
		t_material *out_material,
		__global const t_object *objects,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		int closest_obj_index,
		int closest_polygon_index)
{
	if (isset(closest_obj_index))
	{
		*out_material = objects[closest_obj_index].material;
		return true;
	}
	else if (isset(closest_polygon_index))
	{
		*out_material = get_polygon_material(meshes_info, polygons, closest_polygon_index);
		return true;
	}
	return false;
}
