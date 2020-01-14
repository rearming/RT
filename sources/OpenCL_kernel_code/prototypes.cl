
int			mix_avg_color(t_color col_prev, t_color col_new, int samples);

void		rotate_y(float3 *point, float angle);

void		rotate_x(float3 *point, float angle);

void		rotate_z(float3 *point, float angle);

float3		degree_to_rad(float3 rotation_degrees);

void		rotate_point(float3 *point, float3 angle);

float3			get_img_point(int global_id);

void			correct_img_point(float3 *img_point);

void	rt_main(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __constant t_opencl_params *params,
    __global int *img_data);

float3			canvas_to_viewport(__constant t_camera *camera, float3 canvas_point);

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

t_color		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		float3 ray_dir,
		float3 point,
		float3 normal,
		int bounce_num);

