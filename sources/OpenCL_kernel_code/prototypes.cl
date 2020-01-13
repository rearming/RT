
t_point			get_img_point(int global_id);

void	rt_main(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __constant t_opencl_params *params,
    __global int *img_data);

void				ray_plane_intersect(
		float3 camera_pos,
		float3 ray_dir,
		float3 center,
		float3 normal,
		float *out_x1,
		float *out_x2);

void				ray_sphere_intersect(
		float3 camera_pos,
		float3 ray_dir,
		__constant t_object *sphere,
		float *out_x1,
		float *out_x2);

