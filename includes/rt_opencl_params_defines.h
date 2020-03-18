#ifndef RT_OPENCL_PARAMS_DEFINES_H
# define RT_OPENCL_PARAMS_DEFINES_H

# define OPENCL_KERNEL_NAME "rt_main"

/*
**	device mem types
*/

typedef enum	e_cl_mem_type
{
	RT_CL_MEM_SCENE = 0,
	RT_CL_MEM_OBJECTS,
	RT_CL_MEM_LIGHTS,
	RT_CL_MEM_PARAMS,

	RT_CL_MEM_KD_INFO,
	RT_CL_MEM_KD_TREE,
	RT_CL_MEM_KD_INDICES,
	RT_CL_MEM_MESHES_INFO,
	RT_CL_MEM_POLYGONS,
	RT_CL_MEM_VERTICES,
	RT_CL_MEM_V_NORMALS,
	RT_CL_MEM_V_TEXTURES,

	RT_CL_MEM_TEXTURE_INFO,
	RT_CL_MEM_TEXTURE_LIST,
	RT_CL_MEM_SKYBOX_INFO,
	RT_CL_MEM_SKYBOX_LIST,

	RT_CL_MEM_IMG_DATA,
}				t_cl_mem_type;

/*
**	render states
*/

typedef enum	e_render_state
{
	STATE_NOTHING = 0x0,
	STATE_NO_MESH = (1 << 0),
	STATE_NO_SKYBOX = (1 << 1),
	STATE_NO_TEXTURES = (1 << 2)
}				t_render_state;

/*
**	render options
*/

typedef enum	e_render_options
{
	RENDER_NEVER = 0x0,
	RENDER_ALWAYS = 0b11111111111111111111111111111111,
	RENDER_RAYTRACE = (1 << 0),
	RENDER_PATHTRACE = (1 << 1),
	RENDER_RAYMARCH = (1 << 2),
	RENDER_MESH = (1 << 3),
	RENDER_BACKFACE_CULLING = (1 << 4),
	RENDER_OBJECTS = (1 << 5),
	RENDER_MESH_VTEXTURES = (1 << 6),
	RENDER_TEXTURES = (1 << 7),
	RENDER_ANTI_ALIASING = (1 << 8),
	RENDER_SMOOTH_NORMALS = (1 << 9),
	RENDER_SKYBOX = (1 << 10),
}				t_render_options;

# define RENDER_DEFAULT RENDER_RAYTRACE | /*RENDER_OBJECTS |*/ RENDER_TEXTURES | RENDER_MESH /*| RENDER_BACKFACE_CULLING*/

/*
**	render actions
*/

typedef enum	e_render_action
{
	ACTION_NOTHING = 0x0,
	ACTION_ALL = 0b11111111111111111111111111111111,
	ACTION_CAMERA_CHANGED = (1 << 0),
	ACTION_OBJECTS_CHANGED = (1 << 1),
	ACTION_LIGHTS_CHANGED = (1 << 2),
	ACTION_MESH_CHANGED = (1 << 3),
	ACTION_PARAMS_CHANGED = (1 << 4),
	ACTION_TEXTURES_CHANGED = (1 << 5),
	ACTION_SKYBOX_CHANGED = (1 << 6),
	ACTION_PATHTRACE = (1 << 7),
	ACTION_INIT = (1 << 23),
	ACTION_EXIT = (1 << 24)
}				t_render_action;

# define RT_DEFAULT_MEM_FLAG (CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR)
# define RT_MEM_RW_FLAG (CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR)

# define OPENCL_RELEASE_KERNEL_NUM WIN_WIDTH * WIN_HEIGHT
# define OPENCL_DEBUG_KERNEL_NUM 2

# ifndef FT_OPENCL___
#  define OPENCL_INCLUDE_DIRS \
" -I ./includes " \
" -I ./sources/kernel " \
" -I ./sources/kernel/light_computing " \
" -I ./sources/kernel/mesh_render " \
" -I ./sources/kernel/object_intersections " \
" -I ./sources/kernel/object_intersections/more_difficult_object " \
" -I ./sources/kernel/pathtrace_algo " \
" -I ./sources/kernel/texture_formulas" \
" -I ./sources/kernel/kd_tree_traversal" \
" -I ./sources/kernel/anti_aliasing"
# endif

# ifdef __APPLE__
#  define OPENCL_APPLE_DEFINE "#define __APPLE__\n\n"
# else
#  define OPENCL_APPLE_DEFINE "\n"
# endif

#endif