#ifndef RT_WAVEFRONT_RENDER_H
# define RT_WAVEFRONT_RENDER_H

cl_kernel	*g_wavefront_kernels;

typedef enum e_cl_mem_types t_cl_mem_types;
typedef struct		s_kernel_work_sizes
{
	uint32_t		materials;
	uint32_t		textures;
	uint32_t		skybox;
}					t_kernel_work_sizes;

void			bzero_buffer(t_cl_mem_types mem_index);
void			bzero_float3_temp_img(cl_float3 *zero_arr);
void			rt_set_kernel_args(cl_kernel kernel, int args_num, ...);
void			wavefront_compile_kernels(uint32_t render_flags, t_renderer_params *params);
t_cl_mem_types	switch_ray_buffers(int iteration);
void wavefront_release_buffers(uint32_t current_render_state);
void			rt_wavefront_alloc_buffers(uint32_t render_state, ...);
void wavefront_setup_buffers(t_rt *rt,
							 t_renderer_params render_params,
							 uint32_t render_state,
							 uint32_t max_work_size);

/*
**	wavefront run kernels
*/

float kernel_generate_primary_rays(t_rt *rt, cl_kernel kernel);
float kernel_find_intersections(
		t_rt *rt,
		cl_kernel kernel,
		size_t kernel_work_size,
		t_kernel_work_sizes *out_work_sizes,
		int iteration);
float kernel_raytrace_material_compute_light(
		t_rt *rt,
		cl_kernel kernel,
		size_t kernel_work_size);
float kernel_material_shade(
		t_rt *rt,
		cl_kernel kernel,
		size_t kernel_work_size,
		uint32_t *out_new_rays_buffer_len,
		int iteration);
float kernel_texture_shade(
		t_rt *rt,
		cl_kernel kernel,
		size_t kernel_work_size,
		uint32_t *out_new_rays_buffer_len,
		int iteration);
float kernel_skybox_shade(t_rt *rt, cl_kernel kernel, size_t kernel_work_size);
float kernel_fill_img_data(t_rt *rt, cl_kernel kernel, size_t kernel_work_size);

/*
**	wavefront cl_mem buffers
*/

typedef enum	e_cl_mem_types
{
	RT_CL_MEM_CAMERA = 0,
	RT_CL_MEM_RAYS_BUFFER,
	RT_CL_MEM_PIXEL_INDICES,

	RT_CL_MEM_SCENE,
	RT_CL_MEM_OBJECTS,
	RT_CL_MEM_LIGHTS,
	RT_CL_MEM_KD_INFO,
	RT_CL_MEM_KD_TREE,
	RT_CL_MEM_KD_INDICES,
	RT_CL_MEM_MESH_INFO,
	RT_CL_MEM_POLYGONS,
	RT_CL_MEM_VERTICES,
	RT_CL_MEM_V_NORMALS,
	RT_CL_MEM_V_TEXTURES,

	RT_CL_MEM_MATERIAL_HIT_OBJ_INDICES,
	RT_CL_MEM_MATERIAL_HIT_POLYGON_INDICES,
	RT_CL_MEM_MATERIAL_PIXEL_INDICES,
	RT_CL_MEM_MATERIAL_RAYS_HIT_BUFFER,
	RT_CL_MEM_MATERIAL_BUFFERS_LEN,

	RT_CL_MEM_TEXTURE_HIT_OBJ_INDICES,
	RT_CL_MEM_TEXTURE_HIT_POLYGON_INDICES,
	RT_CL_MEM_TEXTURE_PIXEL_INDICES,
	RT_CL_MEM_TEXTURE_RAYS_HIT_BUFFER,
	RT_CL_MEM_TEXTURE_BUFFERS_LEN,

	RT_CL_MEM_SKYBOX_HIT_PIXEL_INDICES,
	RT_CL_MEM_SKYBOX_HIT_RAYS_BUFFER,
	RT_CL_MEM_SKYBOX_HIT_BUFFERS_LEN,

	RT_CL_MEM_INT_IMG,
	RT_CL_MEM_OUT_RAYS_BUFFER,
	RT_CL_MEM_OUT_RAYS_PIXEL_INDICES,
	RT_CL_MEM_OUT_RAYS_BUFFER_LEN,

	RT_CL_MEM_TEMP_FLOAT3_IMG_DATA,
	RT_CL_MEM_MAIN_FLOAT3_IMG_DATA,
	RT_CL_MEM_RENDERER_PARAMS,
	RT_CL_MEM_LIGHT_INTENSITY_BUFFER,

	RT_CL_MEM_TEXTURE_INFO,
	RT_CL_MEM_TEXTURE_LIST,

	RT_CL_MEM_AA_RAYS_BUFFER,
	RT_CL_MEM_AA_PIXEL_INDICES,
	RT_CL_MEM_AA_RAYS_BUFFER_LEN,
}				t_cl_mem_types;

struct			s_kernels_info
{
	char		*kernel_path;
	char		*kernel_name;
};

enum			e_wavefront_kernels
{
	RT_KERNEL_GENERATE_PRIMARY_RAYS = 0,
	RT_KERNEL_FIND_INTERSECTIONS,
	RT_KERNEL_MATERIAL_COMPUTE_LIGHT,
	RT_KERNEL_MATERIAL_SHADE,
	RT_KERNEL_TEXTURE_SHADE,
	RT_KERNEL_SKYBOX_SHADE,
	RT_KERNEL_FILL_IMG_DATA,
	RT_KERNEL_ANTI_ALIASING_IMG_GEN,
	RT_KERNEL_ANTI_ALIASING_RAYS_GEN,
};

#endif
