#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

typedef unsigned int	t_bool;

typedef struct			s_rgb
{
# ifndef FT_OPENCL___

	cl_uchar			r;
	cl_uchar			g;
	cl_uchar			b;
	cl_uchar			a;
# else

	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		a;
# endif

}						t_rgb;

typedef union			u_color
{
# ifndef FT_OPENCL___

	cl_int			value;
# else

	int				value;
# endif

	t_rgb			rgb;
}						t_color;

typedef struct			s_fpoint
{
# ifndef FT_OPENCL___

	cl_float			x;
	cl_float			y;
	cl_float			z;
# else

	float				x;
	float				y;
	float				z;
# endif
}						t_fpoint;

typedef struct			s_point
{
# ifndef FT_OPENCL___
	cl_int				x;
	cl_int				y;
	cl_int				z;
	t_color				color;
# else
	int					x;
	int					y;
	int					z;
	t_color				color;
# endif
}						t_point;

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

typedef struct			s_cl_mem
{
	cl_mem				mem;
	t_bool				copy_mem;
}						t_cl_mem;

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
	t_cl_mem			*opencl_mem;
	cl_mem				img_data_mem;
	int					opencl_memobj_number;
}						t_opencl;

# endif

typedef struct			s_camera
{
# ifndef FT_OPENCL___

	cl_float			viewport_width;
	cl_float			viewport_height;
	cl_float			viewport_distance;
	cl_float3			pos;
	cl_float3			rotation;
# else

	float				viewport_width;
	float				viewport_height;
	float				viewport_distance;
	float3				pos;
	float3				rotation;
# endif

}						t_camera;

/*
** Objects
*/

typedef enum			e_object_type
{
	SPHERE = 1,
	PLANE,
	CYLINDER,
	CONE,
}						t_object_type;

typedef enum			e_light_type
{
	AMBIENT = 1,
	POINT,
	DIRECTIONAL,
	PARALLEL,
}						t_light_type;

typedef struct			s_light
{
# ifndef FT_OPENCL___

	t_light_type		type;
	cl_float			intensity;
	cl_float3			pos;
	cl_float3			dir;
	cl_float3			color;
# else

	t_light_type		type;
	float				intensity;
	float3				pos;
	float3				dir;
	float3				color;
# endif

}						t_light;

typedef struct			s_material
{
# ifndef FT_OPENCL___

	cl_float3			albedo;
	cl_float3			specular;
	cl_float			smoothness;
	cl_float			transmittance;
	cl_float			refraction;
	cl_float3			emission_color;
	cl_float			emission_power;
	cl_int				texture_number;
	cl_float3			texture_position;
# else

	float3				albedo;
	float3				specular;
	float				smoothness;
	float				transmittance;
	float				refraction;
	float3				emission_color;
	float				emission_power;
	int					texture_number;
	float3				texture_position;
# endif

}						t_material;

typedef struct			s_object
{
# ifndef FT_OPENCL___

	t_object_type		type;
	t_material			material;
	cl_float3			center;
	cl_float3			normal;
	cl_float			radius;
	cl_float			angle;
	cl_float			len;
# else

	t_object_type		type;
	t_material			material;
	float3				center;
	float3				normal;
	float				radius;
	float				angle;
	float				len;
# endif

}						t_object;

typedef struct			s_scene
{
# ifndef FT_OPENCL___

	t_camera			camera;
	cl_int				obj_nbr;
	cl_int				lights_nbr;
	t_object			*objects;
	t_light				*lights;
# else

	t_camera			camera;
	int					obj_nbr;
	int					lights_nbr;
	t_object			*objects;
	t_light				*lights;
# endif

}						t_scene;

typedef enum			e_render_algo
{
	PATH_TRACE = 1,
	RAY_TRACE,
	RAY_MARCH,
}						t_render_algo;

typedef struct			s_pathtrace_params
{
# ifndef FT_OPENCL___

	cl_int				current_samples_num;
	cl_int				max_depth;
# else

	int					current_samples_num;
	int					max_depth;
# endif

}						t_pathtrace_params;

typedef struct			s_raytrace_params
{
# ifndef FT_OPENCL___

	cl_int				max_depth;
# else

	int					max_depth;
# endif

}						t_raytrace_params;

typedef struct			s_opencl_params
{
# ifndef FT_OPENCL___

	t_render_algo		render_algo;
	t_pathtrace_params	pathtrace_params;
	t_raytrace_params	raytrace_params;
	cl_float			seed;
# else

	t_render_algo		render_algo;
	t_pathtrace_params	pathtrace_params;
	t_raytrace_params	raytrace_params;
	float				seed;
# endif
}						t_opencl_params;

# ifndef FT_OPENCL___

typedef struct			s_events
{
	t_bool				w;
	t_bool				a;
	t_bool				s;
	t_bool				d;
	t_bool				info;
	t_bool				space;
	t_bool				lshift;
}						t_events;

typedef struct			s_opencl_mem_obj
{
	void				*ptr;
	size_t				size;
	cl_mem_flags		mem_flags;
	t_bool				copy_mem;
}						t_opencl_mem_obj;

typedef struct			s_rt
{
	t_scene				scene;
	t_opencl_params		opencl_params;
	t_events			events;
}						t_rt;

#  define CL_BUFF_SIZE 10000

typedef struct			s_cl_concat_kernel_code
{
	char				*temp_str;
	char				*backup;
	char				buf[CL_BUFF_SIZE + 1];
	int					read_res;
	size_t				sum_len;
	va_list				ap;
	char				*str_file;
	size_t				file_size;
	int					fd;
}						t_cl_concat_kernel_code;
# endif

#endif
