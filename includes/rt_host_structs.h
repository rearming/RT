#ifndef RT_HOST_STRUCTS_H
# define RT_HOST_STRUCTS_H

# ifndef FT_OPENCL___

#define TEXTURE_BUF 15
typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*texture;
	SDL_Texture			**texture_list;
	int					pitch;
}						t_sdl;

typedef struct			s_cl_buffer
{
	cl_mem				mem;
	u_int32_t			renderer_flags;
	bool				copy_mem;
}						t_cl_buffer;

typedef struct s_rt_renderer t_rt_renderer;

typedef struct			s_opencl
{
	cl_context			context;
	cl_command_queue	queue;
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_device_id		device_id;
	cl_program			program;
	cl_kernel			kernel;
	cl_event			profile_event;
	t_cl_buffer			*opencl_mem;
	cl_mem				img_data_mem;
	int					opencl_memobj_number;
	t_list				*renderers;
}						t_opencl;

typedef struct			s_rt_renderer
{
	uint32_t			flags;
	cl_program			program;
	cl_kernel			kernel;
	t_cl_buffer			*buffers;
	int					buffers_num;
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
	bool				copy;
	uint32_t			renderer_flags;
}						t_opencl_mem_obj;

typedef struct			s_rt
{
	t_scene				scene;
	t_opencl_params		opencl_params;
	t_events			events;
}						t_rt;

# endif
#endif
