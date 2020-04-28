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

typedef struct 			s_tmp
{
	int 			structure_type;	// object, camera, light
	int 			type;			// ambience, sphere, cone
	cl_float3		rotation;		// camera
	cl_float3		pos;			// camera,	light
	float 			intensity;		// 			light
	cl_float3		dir;			// 			light
	cl_float3 		color;			//			light
	cl_float3		normal;			//					object
	cl_float3 		axis;			//					object
	cl_float3 		center;			//					object
	cl_float3		vmin;			//					object
	cl_float3		vmax;			//					object
	float 			distance;		//					object
	float			radius;			//					object
	float			angle;			//					object
	float 			len;			//					object
	cl_float3		ambience;		//					object (material)
	cl_float3		diffuse;		//					object (material)
	cl_float3		specular;		//					object (material)
	float			phong_exp;		//					object (material)
	float			smoothness;		//					object (material)
	float			transmittance;	//					object (material)
	float			refraction;		//					object (material)
	cl_float3 		emission_color;	//					object (material)
	float			emission_power;//					object (material)
	float			specular_texture;//					object (material)
	int 			texture_number; //					object (material)
	cl_float3		texture_position;//					object (material)
	cl_float		alfa_angle;//						object(complicated)
	cl_float		beta_angle;//						object(complicated)
	cl_float		gamma_angle;//						object(complicated)
	cl_float		reverse_alfa_angle;//						object(complicated)
	cl_float		reverse_beta_angle;//						object(complicated)
	cl_float		reverse_gamma_angle;//						object(complicated)
	int				complicated;//						object(complicated)
	int				complicated_index;//				object(complicated)
	cl_int			max_depth_r;	//					render_parameters
	cl_int			max_depth_p;	//					render_parameters
	cl_int			skybox_num;		//					render_parameters
	float			exposure;		//					scene_parameters
	float			gamma;			//					scene_parameters
	char*			file;			//					obj_parameters
	bool 			checker[40];
	struct s_tmp	*next;
}						t_tmp;

# endif
#endif
