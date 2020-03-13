#ifndef RT_HOST_STRUCTS_H
# define RT_HOST_STRUCTS_H

# ifndef FT_OPENCL___

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*texture;
	int					pitch;
	SDL_Window			*win_tool;
	SDL_Surface			*surface;
}						t_sdl;

typedef struct			s_cl_buffer
{
	cl_mem				mem;
	uint32_t			renderer_flags;
	uint32_t			realloc_state;
}						t_cl_buffer;

typedef struct s_rt_renderer t_rt_renderer;

typedef struct			s_opencl
{
	cl_context			context;
	cl_command_queue	queue;
	cl_platform_id		platform_ids[2];
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_device_id		device_id;
	cl_event			profile_event;
	cl_mem				img_data_mem;
	t_list				*renderers;

	t_cl_buffer			*wf_shared_buffers;
	int					wf_shared_buffers_len;
}						t_opencl;

typedef struct			s_rt_renderer
{
	uint32_t			flags;
	t_renderer_params	params;
	cl_program			main_program;
	cl_kernel			main_kernel;
	t_cl_buffer			*buffers;
	int					buffers_num;
	bool				copy_done;
	cl_program			img_gen_program;
	cl_kernel			img_gen_kernel;
	cl_mem				primary_img;
	cl_program			ray_gen_program;
	cl_kernel			ray_gen_kernel;
	cl_mem				rays_buffer;
}						t_rt_renderer;

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

typedef struct			s_events
{
	bool				w;
	bool				a;
	bool				s;
	bool				d;
	bool				info;
	bool				space;
	bool				lshift;
}						t_events;

typedef struct			s_opencl_mem_obj
{
	void				*ptr;
	size_t				size;
	cl_mem_flags		mem_flags;
	uint32_t			realloc_state;
	uint32_t			renderer_flags;
//	uint32_t			kernel_type_flags;
}						t_opencl_mem_obj;

typedef struct			s_rt
{
	t_scene				scene;
	uint32_t			render_settings;
	uint32_t			render_state;
	t_events			events;
	t_kd_info			kd_info;
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
	bool 			checker[28];
	struct s_tmp	*next;
}						t_tmp;

# endif
#endif
