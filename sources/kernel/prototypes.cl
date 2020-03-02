
float3		mix_avg_colors(float3 col_prev, float3 col_new, int samples);

float3		mix_colors(float3 col1, float3 col2, float t);

float3		get_float3_color(int hex_color);

float		color_energy(float3 color);

int			get_int_color(float3 color);

int         get_texture_color(
		int2 pos,
		__constant float *texture_list,
		__constant t_texture_info *texture_info
);

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

float3	gram_schmidt_proc_r2(float3 vector_orto, float3 vector_basic);

float3		vec_axis_rotate(float3 vec, float3 axis, float angle);

float3		float3_float_mult(float3 vec, float num);

float3		sobel_get_pixel(__global __read_only const int *img, int x, int y);

float		sobel_get_weight_x(__global __read_only const int *img, int img_x, int img_y);

float		sobel_get_weight_y(__global __read_only const int *img, int img_x, int img_y);

float3		shade(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		__global const t_object *object);

float3		raytrace(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_light *lights,
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		__global const float3 *v_textures,
		__global const t_renderer_params *params,
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		t_ray ray);

bool		get_hit_material(
		t_material *out_material,
		__global const t_object *objects,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		__global const float3 *v_textures,
		int closest_obj_index,
		int closest_polygon_index);

bool						ft_stack_push(t_stack *stack, t_kd_traverse_helper helper);

t_kd_traverse_helper		ft_stack_pop(t_stack *stack);

t_kd_traverse_helper		ft_stack_peek(t_stack *stack);

float3			canvas_to_viewport(__global const t_camera *camera, float3 canvas_point);

float3		reflect(float3 ray_dir, float3 normal);

float3		convex_refract(float3 ray_dir, float3 normal, float refract_index);

float3		concave_refract(float3 ray_dir, float3 normal, float refract_index);

bool		isset(int value);

float		saturate(float value);

float3		saturate_float3(float3 value);

bool		ray_has_energy(t_ray *ray);

int3		get_img_point(int global_id);

void			correct_img_point(float3 *img_point);

t_ray			get_ray(float3 img_point, __global __read_only const t_camera *camera);

float3			correct_hdr(float gamma, float exposure, float3 hdr_color);

bool		ray_aabb_traverse_intersection(t_ray *ray, t_aabb aabb, float *out_near, float *out_far);

void		kd_swap_nodes(
		bool need_swap,
		int left_index,
		int right_index,
		int *out_first,
		int *out_second);

__global const t_kd_arr_tree	*kd_get_node(
		__global const t_kd_arr_tree *arr,
		__global const t_kd_arr_tree *curr_node,
		int side);

float	f3_axis(float3 vec, int axis);

int		kd_tree_traverse(
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *tree_arr,
		__global const int *kd_indices,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit);

bool				in_shadow(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_light_type light_type);

float				blinn_phong_shine(float3 ray_dir, float3 light_dir, float3 normal, float phong_exp);

float				compute_light(
	__global const t_scene *scene,
	__global const t_light *lights,
	__global const t_object *objects,
	__global const t_kd_info *kd_info,
	__global const t_kd_arr_tree *kd_tree,
	__global const int *kd_indices,
	__global const t_mesh_info *meshes_info,
	__global const t_polygon *polygons,
	__global const float3 *vertices,
	__global const float3 *v_normals,
	__global const float3 *v_textures,
	t_rayhit *hit,
	t_ray *ray,
	t_material *hit_material);

int		ray_mesh_intersect(
		__global const t_meshes *mesh_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit);

t_material	get_polygon_material(
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		int polygon_index);

void				closest_intersection(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		t_ray *ray,
		t_rayhit *out_best_hit,
		int *out_closest_polygon_index,
		int *out_closest_obj_index);

bool		ray_aabb_intersection(t_ray *ray, __global const t_object *object, t_rayhit *best_hit);

bool				ray_triangle_intersect_MT(
		t_ray *ray,
		__global const t_object *triangle,
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
		__global const t_object *sphere,
		t_rayhit *best_hit);

bool				ray_cone_intersect(
		t_ray *ray,
		__global const t_object *cone,
		t_rayhit *best_hit);

bool				ray_cylinder_intersect(
		t_ray *ray,
		__global const t_object *cylinder,
		t_rayhit *best_hit);

bool				ray_paraboloid_intersect(
		t_ray *ray,
		__global const t_object *paraboloid,
		t_rayhit *best_hit);

bool				ray_ellipsoid_intersect(
		t_ray *ray,
		__global const t_object *ellipsoid,
		t_rayhit *best_hit);

float3		pathtrace(
		__global const t_scene *scene,
		__global const t_object *objects,
		__global const t_kd_info *kd_info,
		__global const t_kd_arr_tree *kd_tree,
		__global const int *kd_indices,
		__global const t_mesh_info *meshes_info,
		__global const t_polygon *polygons,
		__global const float3 *vertices,
		__global const float3 *v_normals,
		__global const float3 *v_textures,
		__global const t_renderer_params *params,
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
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

void		calc_refraction_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		float3 color,
		float *seed,
		float2 pixel,
		float chance);

void		calc_reflection_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material *material,
		float3 color,
		float *seed,
		float2 pixel,
		float chance);

float3		shade_pathtrace(
		t_ray *ray,
		t_rayhit *hit,
		t_material material,
		float *seed,
		float2 pixel);

float3		texture_shade_pathtrace(
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		__global const t_object *object,
		t_ray *ray,
		t_rayhit *hit,
		t_material material,
		float *seed,
		float2 pixel);

float3		skybox_color(
		__global const t_texture_info *texture_info,
		__global const float *texture_list,
		float3 normal);

float 		scale(t_ray ray, float skybox_radius);

float3		skybox_normal(t_ray ray);

void 	change_format(int i_color, float3 *f_color);

float3 texture(t_ray *out_ray,
			   t_rayhit *hit,
			   __global const t_texture_info *texture_info,
			   __global const float *texture_list,
			   __global const t_object *object);

int		check_borders(int a, int max, int type);

