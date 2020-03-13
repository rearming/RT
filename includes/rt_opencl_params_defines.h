#ifndef RT_OPENCL_PARAMS_DEFINES_H
# define RT_OPENCL_PARAMS_DEFINES_H

# define MAIN_KERNEL_PATH "./sources/kernel/rt_main.cl"
# define IMG_GEN_KERNEL_PATH "./sources/kernel/img_gen_main.cl"
# define RAYS_GEN_KERNEL_PATH "./sources/kernel/rays_gen_main.cl"

# define MAIN_KERNEL_NAME "rt_main"
# define IMG_GEN_KERNEL_NAME "img_gen"
# define RAYS_GEN_KERNEL_NAME "rays_gen"

/*
**	renderers params
*/

typedef enum	e_render_settings
{
	RENDER_NEVER = 0x0,
	RENDER_ALWAYS = 0b1111111111111111,
	RENDER_RAYTRACE = (1 << 0),
	RENDER_PATHTRACE = (1 << 1),
	RENDER_RAYMARCH = (1 << 2),
	RENDER_MESH = (1 << 3),
	RENDER_BACKFACE_CULLING = (1 << 4),
	RENDER_OBJECTS = (1 << 5),
	RENDER_MESH_VTEXTURES = (1 << 6),
	RENDER_TEXTURES = (1 << 7),
	RENDER_ANTI_ALIASING = (1 << 8),
}				t_renderer_settings;

# define RENDER_DEFAULT RENDER_RAYTRACE | /*RENDER_OBJECTS |*/ RENDER_TEXTURES | RENDER_MESH /*| RENDER_BACKFACE_CULLING*/

/*
**	render states
*/

typedef enum	e_gpu_mem_realloc_states{
	STATE_NOTHING = 0x0,
	STATE_ALL = 0b11111111111111111111111111111111,
	STATE_CAMERA_CHANGED = (1 << 0),
	STATE_OBJECTS_CHANGED = (1 << 1),
	STATE_LIGHTS_CHANGED = (1 << 2),
	STATE_MESH_CHANGED = (1 << 3),
	STATE_PARAMS_CHANGED = (1 << 4),
	STATE_TEXTURES_CHANGED = (1 << 5),
	STATE_AA_RAYS_GENERATED = (1 << 6),
	STATE_NO_AA_INIT = (1 << 7),
	STATE_INIT = (1 << 23),
	STATE_EXIT = (1 << 24)
}				t_gpu_mem_realloc_states;

# define RT_DEFAULT_MEM_FLAG (CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR)
# define RT_MEM_RW_FLAG (CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR)

# define OPENCL_RELEASE_KERNEL_NUM WIN_WIDTH * WIN_HEIGHT
# define OPENCL_DEBUG_KERNEL_NUM 2

# ifndef FT_OPENCL___
#  define OPENCL_INCLUDE_DIRS \
" -I ./includes " \
" -I ./sources/kernel " \
" -I ./sources/kernel/raytrace " \
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