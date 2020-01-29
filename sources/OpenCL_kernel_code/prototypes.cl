
float3		mix_avg_colors(float3 col_prev, float3 col_new, int samples);

float3		mix_colors(float3 col1, float3 col2, float t);

float3		get_float3_color(int hex_color);

float		color_energy(float3 color);

int			get_int_color(float3 color);

float		sdot(float3 a, float3 b, float coeff);

int 				in_range_inclusive(float number, float min, float max);

uint		rt_rand(uint seed);

float		rt_fract(float x);

float		rt_randf(float *seed, float2 pixel);

void		rotate_y(float3 *point, float angle);

void		rotate_x(float3 *point, float angle);

void		rotate_z(float3 *point, float angle);

float3		degree_to_rad(float3 rotation_degrees);

void		rotate_point(float3 *point, float3 angle);

float3		shade(
		t_ray *ray,
		t_rayhit *hit,
		__constant t_material *material);

float3		raytrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_polygon *polygons,
		__constant float3 *vertices,
		__constant float3 *v_normals,
		__constant t_opencl_params *params,
		t_ray ray);

float3			get_img_point(int global_id);

void			correct_img_point(float3 *img_point);

t_ray			get_ray(float3 img_point, __constant t_camera *camera);

float3			correct_hdr(float gamma, float exposure, float3 hdr_color);

void	rt_main(
    __constant t_scene *scene,
    __constant t_object *objects,
    __constant t_light *lights,
    __constant t_opencl_params *params,
    __global float3 *img_data_float,
    __constant t_polygon *polygons,
	__constant float3 *vertices,
	__constant float3 *v_normals,
    __global int *img_data);

float3			canvas_to_viewport(__constant t_camera *camera, float3 canvas_point);

float3		reflect(float3 ray_dir, float3 normal);

float3		refract(float3 ray_dir, float3 normal, float refract_index);

float		saturate(float value);

float3		saturate_float3(float3 value);

bool		ray_has_energy(t_ray *ray);

bool				in_shadow(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_polygon *polygons,
		__constant float3 *vertices,
		__constant float3 *v_normals,
		t_ray *ray,
		t_light_type light_type);

float				compute_light(
	__constant t_scene *scene,
	__constant t_light *lights,
	__constant t_object *objects,
	__constant t_polygon *polygons,
	__constant float3 *vertices,
	__constant float3 *v_normals,
	t_rayhit *hit);

void				closest_intersection(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_polygon *polygons,
		__constant float3 *vertices,
		__constant float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit,
		int *out_closest_polygon_index,
		int *out_closest_obj_index);

int		ray_mesh_intersect(
		__constant t_meshes *mesh_info,
		__constant t_polygon *polygons,
		__constant float3 *vertices,
		__constant float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit);

bool				ray_triangle_intersect_MT(
		t_ray *ray,
		__constant t_object *triangle,
		t_rayhit *best_hit);

bool				ray_triangle_intersect_MT_polygon(
		float3 v0, float3 v1, float3 v2,
		float3 vn,
		float3 vt0, float3 vt1, float3 vt2,
		t_ray *ray,
		t_rayhit *best_hit);

bool				ray_plane_intersect(
		t_ray *ray,
		float3 center,
		float3 normal,
		t_rayhit *best_hit);

bool				ray_sphere_intersect(
		t_ray *ray,
		__constant t_object *sphere,
		t_rayhit *best_hit);

float3		pathtrace(
		__constant t_scene *scene,
		__constant t_object *objects,
		__constant t_light *lights,
		__constant t_polygon *polygons,
		__constant float3 *vertices,
		__constant float3 *v_normals,
		__constant t_opencl_params *params,
		t_ray ray,
		int depth,
		float *seed,
		float2 pixel);

void		create_coordinate_system(float3 normal, float3 *normal_x, float3 *normal_z);

float3		sample_hemisphere(float *seed, float2 pixel, float phong_alpha);

float3		rand_dir_on_hemisphere(
		float3 normal,
		float *seed,
		float2 pixel,
		float phong_alpha);

float3		shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		__constant t_material *material,
		float *seed,
		float2 pixel);

