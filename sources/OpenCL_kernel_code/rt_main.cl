float3			get_img_point(int global_id)
{
	return (float3)(global_id % WIN_WIDTH, global_id / WIN_HEIGHT, 0);
}

void			correct_img_point(float3 *img_point)
{
	img_point->x -= WIN_WIDTH / 2;
	img_point->y -= WIN_HEIGHT / 2;
	img_point->y = -img_point->y;
}

__kernel void	rt_main(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __constant t_opencl_params *params,
    __global int *img_data)
{
	int			g_id = get_global_id(0);
	float3		img_point = get_img_point(g_id);

	correct_img_point(&img_point);
	float3	ray_dir = fast_normalize(canvas_to_viewport(&scene->camera, img_point));
	rotate_point(&ray_dir, scene->camera.rotation);

	t_color		new_color;
	t_color		prev_color = { img_data[g_id] };

	if (params->render_algo == PATHTRACE)
		new_color = pathtrace(scene, objects, lights, params, ray_dir, (float3)(0), (float3)(0), 0);
	img_data[g_id] = mix_avg_color(prev_color, new_color, params->pathtrace_params.current_samples_num);
}
