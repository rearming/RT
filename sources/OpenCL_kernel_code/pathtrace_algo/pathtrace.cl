
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

	t_rayhit	besthit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
	int			closes_index = NOT_SET;

	closest_intersection(scene, objects, &ray, &besthit, &closes_index);
	if (closes_index == NOT_SET)
		return get_float3_color(COL_GREY);
//	result_color = objects[closes_index].material.albedo * shade(&ray, &besthit);
	return result_color;
}