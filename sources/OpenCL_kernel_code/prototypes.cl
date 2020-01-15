
int			mix_avg_color(t_color col_prev, t_color col_new, int samples);

t_color				change_color_intensity(t_color color, float intensity);

t_color				change_color_intensity_colors(t_color target_color, t_color light_color);

float		rand_distribution(uint rand_num);

int 				in_range_inclusive(float number, float min, float max);

uint		rt_rand(uint seed);

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

bool				in_shadow(
		__constant t_scene *scene,
		__constant t_object *objects,
		float3 point,
		float3 light_dir,
		float ray_max);

t_color				compute_lighting(
	__constant t_scene *scene,
	__constant t_light *lights,
	__constant t_object *objects,
	float3 ray_dir,
	float3 point,
	float3 normal);

void find_intersection(
		float3 origin,
		float3 ray_dir,
		__constant t_object *object,
		float *out_intersect1,
		float *out_intersect2);

float				closest_intersection(
		__constant t_scene *scene,
		__constant t_object *objects,
		float3 origin,
		float3 ray_dir,
		float ray_min,
		float ray_max,
		int *out_closest_obj_index,
		t_color *out_result_color);

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

float3			compute_normal(float3 point, __constant t_object *intersect_obj);

void		create_coordinate_system(float3 normal, float3 *normal_x, float3 *normal_z);

float3		uniform_sample_hemisphere(float rand1, float rand2);

float3		rand_dir_on_hemisphere(
		float3 normal,
		float rand1,
		float rand2);

t_color		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		float3 ray_dir,
		float3 origin,
		float3 normal,
		int depth,
		uint random_num);

