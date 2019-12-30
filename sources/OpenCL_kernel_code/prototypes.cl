
t_point			get_img_point(int global_id);

void	rt(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __global int *img_data);

