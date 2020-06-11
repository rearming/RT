#ifndef RT_HOST_STRUCTS_H
# define RT_HOST_STRUCTS_H

# ifndef FT_OPENCL___

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*texture;
	int					pitch;
	SDL_Surface			*surface;
}						t_sdl;

typedef struct			s_cl_buffer
{
	cl_mem				mem;
	uint32_t			render_action;
}						t_cl_buffer;

typedef struct			s_render_kernel
{
	cl_kernel			kernel;
	uint32_t			options;
	cl_mem				img_data_float;
	int					samples_num;
}						t_render_kernel;

typedef struct			s_opencl
{
	cl_context			context;
	cl_command_queue	queue;
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_device_id		device_id;
	cl_event			profile_event;
	t_cl_buffer			*buffers;
	int					buffers_num;
	t_list				*render_kernels;
	cl_kernel			*kernels;
}						t_opencl;

typedef struct			s_obj_material
{
	cl_float3			ambient;
	cl_float3			diffuse;
	cl_float3			specular;
	cl_float3			emission;
	cl_float			phong_exp;
	cl_float			transmittance;
	cl_float			refraction;
}						t_obj_material;

typedef struct			s_opencl_mem_obj
{
	void				*ptr;
	size_t				size;
	cl_mem_flags		mem_flags;
	uint32_t			render_action;
}						t_opencl_mem_obj;

typedef struct			s_rt
{
	t_scene				scene;
	t_kd_info			kd_info;
	t_render_params		params;
	uint32_t			render_state;
	uint32_t			render_options;
	uint32_t			render_actions;
	uint32_t			events;
}						t_rt;

typedef struct			s_tmp
{
	int					struct_type;
	int					type;
	cl_float3			rotation;
	cl_float3			pos;
	float				intensity;
	cl_float3			dir;
	cl_float3			color;
	cl_float3			normal;
	cl_float3			axis;
	cl_float3			center;
	cl_float3			vmin;
	cl_float3			vmax;
	float				distance;
	float				radius;
	float				radius_2;
	float				radius_ring;
	cl_float3			size;
	float				param_0;
	cl_float3			param_1;
	float				angle;
	float				len;
	cl_float3			ambience;
	cl_float3			diffuse;
	cl_float3			specular;
	float				phong_exp;
	float				smoothness;
	float				transmittance;
	float				refraction;
	cl_float3			emission_color;
	float				emission_power;
	float				specular_texture;
	int					texture_number;
	cl_float3			texture_position;
	bool				texture_pbr;
	int					texture_normal;
	float				texture_pbr_index;
	cl_float			alfa_angle;
	cl_float			beta_angle;
	cl_float			gamma_angle;
	int					raymarch;
	int					raymarch_index;
	cl_int				max_depth_r;
	cl_int				max_depth_p;
	cl_int				skybox_num;
	float				exposure;
	float				gamma;
	char				*file;
	bool				checker[45];
	struct s_tmp		*next;
}						t_tmp;

# endif

#endif
