#ifndef RT_SHARED_STRUCTS_H
# define RT_SHARED_STRUCTS_H

typedef struct			s_rgb
{
# ifndef FT_OPENCL___

	cl_uchar			b;
	cl_uchar			g;
	cl_uchar			r;
	cl_uchar			a;
# else

	unsigned char		b;
	unsigned char		g;
	unsigned char		r;
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

typedef struct			s_texture_info
{
# ifndef FT_OPENCL___

	cl_int				width;
	cl_int				height;
	cl_int				start;
	cl_int				bpp;
# else

	int					width;
	int					height;
	int 				start;
	int					bpp;
# endif
}						t_texture_info;

typedef struct		s_texture_name
{
	char 			*name;
	struct s_texture_name *next;
}					t_texture_name;

# ifndef FT_OPENCL___
typedef struct			s_textures
{
	cl_float 			*texture_list;
	t_texture_info		*texture_info; //вот здесь используется количество текстур
	size_t				texture_list_size;
	size_t				texture_info_size; // вот это заполнять
	//char 				**textures_name;
	t_texture_name		*textures_names;
}						t_textures;
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
	TRIANGLE,
	AABB,
	PARABOLOID,
	ELLIPSOID
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

typedef struct			s_material //есть default material и все задается по default
{
# ifndef FT_OPENCL___

	cl_float3			ambient;
	cl_float3			diffuse;
	cl_float3			specular;
	cl_float			phong_exp;
	cl_float			smoothness; // [0.0, 1.0]
	cl_float			transmittance;
	cl_float			refraction;
	cl_float3			emission_color; //color может быть задан 3 способами как 3 int, 3 float, и 1 char
	cl_float			emission_power;
	cl_float			specular_texture;
	cl_int				texture_number;
	cl_float3			texture_position;
# else

	float3				ambient;
	float3				diffuse;
	float3				specular;
	float				phong_exp;
	float				smoothness;
	float				transmittance;
	float				refraction;
	float3				emission_color;
	float				emission_power;
	float				specular_texture;
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
	cl_float3			axis;
	/// axis for all rotation object
	/// (cylinder, cone, torus, hiperboloid etc)
	cl_float			radius;
	cl_float			angle;
	cl_float 			distance;
	cl_float			len;
	cl_float3			vertices[3]; //it's for .obj
	cl_float3			vmin;
	cl_float3			vmax;
# else

	t_object_type		type;
	t_material			material;
	float3				center;
	float3				normal;
	float3				axis;
	///axis for all rotation object
	/// (cylinder, cone, torus, hiperboloid etc)
	float				radius;
	float				angle;
	float 				distance;
	float				len;
	float3				vertices[3];
	float3				vmin;
	float3				vmax;
# endif

}						t_object;

# define RT_DEFAULT_POLYGON_VERTICES 3

typedef struct			s_mesh_info
{
# ifndef FT_OPENCL___

	t_material			material;
# else

	t_material			material;
# endif
}						t_mesh_info;

typedef struct			s_polygon
{
# ifndef FT_OPENCL___

	cl_int				vert_i[RT_DEFAULT_POLYGON_VERTICES];
	cl_int				vnorm_i;
	cl_int				vtex_i[RT_DEFAULT_POLYGON_VERTICES];
	cl_int				mesh_index;
# else

	int					vert_i[RT_DEFAULT_POLYGON_VERTICES];
	int					vnorm_i;
	int					vtex_i[RT_DEFAULT_POLYGON_VERTICES];
	int					mesh_index;
#endif

}						t_polygon;

typedef struct			s_meshes
{
# ifndef FT_OPENCL___

	cl_int				num_polygons;
	cl_int				num_vertices;
	cl_int				num_v_normals;
	cl_int				num_v_textures;
	cl_int				num_meshes;
	t_mesh_info			*meshes_info;
	t_polygon			*polygons;
	cl_float3			*vertices;
	cl_float3			*v_normals;
	cl_float3			*v_textures;
# else

	int					num_polygons;
	int					num_vertices;
	int					num_v_normals;
	int					num_v_textures;
	int					num_meshes;
	t_mesh_info			*meshes_info;
	t_polygon			*polygons;
	float3				*vertices;
	float3				*v_normals;
	float3				*v_textures;
# endif

}						t_meshes;

typedef struct			s_scene
{
# ifndef FT_OPENCL___

	t_camera			camera;
	cl_int				obj_nbr;
	cl_int				lights_nbr;
	t_meshes			meshes;
	t_object			*objects;
	t_light				*lights;
# else

	t_camera			camera;
	int					obj_nbr;
	int					lights_nbr;
	t_meshes			meshes;
	t_object			*objects;
	t_light				*lights;
# endif

}						t_scene;

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

typedef struct			s_renderer_params
{
# ifndef FT_OPENCL___

	t_pathtrace_params	pathtrace_params;
	t_raytrace_params	raytrace_params;
	cl_float			seed;
	cl_float			exposure;
	cl_float			gamma;
# else

	t_pathtrace_params	pathtrace_params;
	t_raytrace_params	raytrace_params;
	float				seed;
	float				exposure;
	float				gamma;
# endif
}						t_renderer_params;

typedef struct		s_aabb
{
#ifndef FT_OPENCL___
	cl_float3		min;
	cl_float3		max;
#else
	float3			min;
	float3			max;
#endif
}					t_aabb;

typedef struct		s_aabb_objects
{
#ifndef FT_OPENCL___
	cl_int			num;
	cl_int			*indices;
#else
	int				num;
	int				*indices;
#endif
}					t_aabb_objects;

# define KD_LEFT 1
# define KD_RIGHT 2

typedef struct		s_kd_arr_node
{
#ifndef FT_OPENCL___
	cl_int			left_index;
	cl_int			right_index;
	cl_float		sah;
	cl_float		split;
	cl_int			split_axis;
	cl_int			obj_offset;
	t_aabb			aabb;
	t_aabb_objects	objects;
#else
	int				left_index;
	int				right_index;
	float			sah;
	float			split;
	int				split_axis;
	int				obj_offset;
	t_aabb			aabb;
	t_aabb_objects	objects;
#endif
}					t_kd_arr_tree;

typedef struct			s_kd_info
{
#ifndef FT_OPENCL___
	cl_int				nodes_num;
	cl_int				indices_num;
	t_kd_arr_tree		*tree_arr;
	cl_int				*indices;
#else
	int					nodes_num;
	int					indices_num;
	t_kd_arr_tree		*tree_arr;
	int					*indices;
#endif
}						t_kd_info;

#endif
