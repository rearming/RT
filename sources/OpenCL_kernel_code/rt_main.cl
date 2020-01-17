
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

t_ray			get_ray(float3 img_point, __constant t_camera *camera)
{
	t_ray		ray;

	correct_img_point(&img_point);
	ray.dir = fast_normalize(canvas_to_viewport(camera, img_point));
	rotate_point(&ray.dir, camera->rotation);
	ray.origin = camera->pos;
	ray.energy = (float3)(1.0f, 1.0f, 1.0f);
	return ray;
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

	t_ray		ray = get_ray(img_point, &scene->camera);
	float3		new_color = (float3)(0);
	float3		prev_color = get_float3_color(img_data[g_id]);

	if (params->render_algo == PATH_TRACE)
		new_color = pathtrace(scene, objects, lights, params, ray, 0, params->randoms * g_id);
	else if (params->render_algo == RAY_TRACE)
		new_color = raytrace(scene, objects, lights, params, ray);
	img_data[g_id] = get_int_color(mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num));
}
