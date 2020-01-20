
float3		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		t_ray ray,
		int depth,
		uint random_num)
{
	float3		result_color = (float3)(0);
	t_rayhit	best_hit = (t_rayhit){(float3)(0), INFINITY, (float3)(0)};
	int			closest_obj_index = NOT_SET;

	closest_intersection(scene, objects, &ray, &best_hit, &closest_obj_index);
	if (closest_obj_index == NOT_SET)
		return get_float3_color(COL_GREY);
//	result_color = objects[closest_obj_index].material.albedo * shade(&ray, &besthit);
	return result_color;
}