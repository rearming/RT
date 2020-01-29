
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

t_ray			get_ray(float3 img_point, __global const t_camera *camera)
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
    __global const t_scene *scene,
    __global const t_object *objects,
    __global const t_light *lights,
    __global const t_opencl_params *params,
    __global const t_polygon *polygons,
	__global const float3 *vertices,
	__global const float3 *v_normals,
    __global float3 *img_data_float,
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
		new_color = pathtrace(scene, objects, lights, polygons, vertices, v_normals,
				params, ray,
				params->pathtrace_params.max_depth, &seed, (float2)(img_point.xy + 1));
		final_color = mix_avg_colors(prev_color, new_color, params->pathtrace_params.current_samples_num);
		img_data_float[g_id] = final_color;
	}
	else if (params->render_algo == RAY_TRACE)
		final_color = raytrace(scene, objects, lights, polygons, vertices, v_normals, params, ray);
	img_data[g_id] = get_int_color(correct_hdr(params->gamma, params->exposure, final_color));
}
