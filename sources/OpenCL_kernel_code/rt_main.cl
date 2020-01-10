t_point			get_img_point(int global_id)
{
	return (t_point){global_id % WIN_WIDTH, global_id / WIN_HEIGHT};
}

__kernel void	rt_main(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __global int *img_data)
{
	t_point img_point = get_img_point(get_global_id(0));

}
