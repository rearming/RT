
float3		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		t_ray ray,
		int depth,
		uint random_num)
{
	float3		result_color = mix_colors(get_float3_color(COL_RED), get_float3_color(COL_GREEN), 0.5);

	t_rayhit	besthit;
	int			closest_obj_index;

	closest_intersection(scene, objects, ray, &besthit, &closest_obj_index);
	result_color = objects[closest_obj_index].material.albedo;
	return result_color;
}