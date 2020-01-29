
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

float3			correct_hdr(float gamma, float exposure, float3 hdr_color)
{
	float3	mapped = (float3)(1.0f) - exp(-hdr_color * exposure);
	mapped = pow(mapped, (float3)(1.0f / gamma));

	return mapped;
}

__kernel void	rt_main(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __constant t_opencl_params *params,
    __global float3 *img_data_float,
    __constant t_polygon *polygons,
	__constant float3 *vertices,
	__constant float3 *v_normals,
    __global int *img_data)
{
	int			g_id = get_global_id(0);
	float3		img_point = get_img_point(g_id);

	t_ray		ray = get_ray(img_point, &scene->camera);

	float3		final_color = 0;
	float3		new_color = 0;
	float3		prev_color = img_data_float[g_id];

	float		seed = params->seed;

	if (params->render_algo == PATH_TRACE)
	{
		new_color = pathtrace(scene, objects, lights, params, ray,
				params->pathtrace_params.max_depth, &seed, (float2)(img_point.xy + 1));
		final_color = mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num);
		img_data_float[g_id] = final_color;
	}
	else if (params->render_algo == RAY_TRACE)
		final_color = raytrace(scene, objects, lights, params, ray);
	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));
//	img_data[g_id] = get_int_color(saturate_float3(final_color));
}
