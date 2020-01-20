
float3		mix_avg_colors(float3 col_prev, float3 col_new, int samples);

float3		mix_colors(float3 col1, float3 col2, float t);

float3		get_float3_color(int hex_color);

int			get_int_color(float3 color);

float		rand_distribution(uint rand_num);

int 				in_range_inclusive(float number, float min, float max);

uint		rt_rand(uint seed);

void		rotate_y(float3 *point, float angle);

void		rotate_x(float3 *point, float angle);

void		rotate_z(float3 *point, float angle);

float3		degree_to_rad(float3 rotation_degrees);

void		rotate_point(float3 *point, float3 angle);

float3		reflect(t_ray *ray, float3 hit_normal);

float		saturate(float value);

float3		shade(
		t_ray *out_ray,
		t_rayhit *hit,
		__constant t_material *material);

bool		ray_has_energy(t_ray *ray);

float3		raytrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		t_ray ray);

float3			get_img_point(int global_id);

void			correct_img_point(float3 *img_point);

t_ray			get_ray(float3 img_point, __constant t_camera *camera);

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
		t_ray *ray,
		t_light_type light_type);

float				compute_light(
	__constant t_scene *scene,
	__constant t_light *lights,
	__constant t_object *objects,
	t_rayhit *hit);

void				closest_intersection(
		__constant t_scene *scene,
		__constant t_object *objects,
		t_ray *ray,
		t_rayhit *out_best_hit,
		int *out_closest_obj_index);

t_bool				ray_plane_intersect(
		t_ray *ray,
		float3 center,
		float3 normal,
		t_rayhit *best_hit);

t_bool				ray_sphere_intersect(
		t_ray *ray,
		__constant t_object *sphere,
		t_rayhit *out_best_hit);

float3		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_opencl_params *params,
		t_ray ray,
		int depth,
		uint random_num);

void		create_coordinate_system(float3 normal, float3 *normal_x, float3 *normal_z);

float3		uniform_sample_hemisphere(float rand1, float rand2);

float3		rand_dir_on_hemisphere(
		float3 normal,
		float rand1,
		float rand2);

