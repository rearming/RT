t_point			get_img_point(int global_id)
{
	return (t_point){global_id % WIN_WIDTH, global_id / WIN_HEIGHT};
}

__kernel void	rt_main(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __constant t_opencl_params *params,
    __global int *img_data)
{
	int			g_id = get_global_id(0);
	t_point		img_point = get_img_point(g_id);

//	printf("img_data: [%p]\n", img_data);
//	if (g_id % 3 == 0)
	if (img_point.x > WIN_WIDTH / 2)
		img_data[g_id] = COL_GREEN;
	else
		img_data[g_id] = COL_BLUE;
//	else if (g_id % 3 == 1)
//		img_data[g_id] = COL_BLUE;
//	else if (g_id % 3 == 2)
//		img_data[g_id] = COL_PURPLE;
}
