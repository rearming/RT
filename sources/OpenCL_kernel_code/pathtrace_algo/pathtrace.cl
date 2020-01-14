t_color		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		float3 ray_dir,
		float3 point,
		float3 normal,
		int bounce_num)
{
	t_color		result_color = { COL_BG };

	if (bounce_num >= params->pathtrace_params.max_bounces)
		return (result_color);

	return result_color;
}