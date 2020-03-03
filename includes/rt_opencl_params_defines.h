#ifndef RT_OPENCL_PARAMS_DEFINES_H
# define RT_OPENCL_PARAMS_DEFINES_H

# define MAIN_KERNEL_PATH "./sources/kernel/rt_main.cl"
# define IMG_GEN_KERNEL_PATH "./sources/kernel/img_gen_main.cl"
# define RAYS_GEN_KERNEL_PATH "./sources/kernel/rays_gen_main.cl"

# define MAIN_KERNEL_NAME "rt_main"
# define IMG_GEN_KERNEL_NAME "img_gen"
# define RAYS_GEN_KERNEL_NAME "rays_gen"

/*
**	cl_mem buffers
*/

typedef enum	e_cl_mem_types
{
	RT_CL_MEM_CAMERA = 0,
	RT_CL_MEM_RAYS_BUFFER,
	RT_CL_MEM_PIXEL_INDICES,
	RT_CL_MEM_SCENE,
	RT_CL_MEM_OBJECTS,
	RT_CL_MEM_KD_INFO,
	RT_CL_MEM_KD_TREE,
	RT_CL_MEM_KD_INDICES,
	RT_CL_MEM_MESH_INFO,
	RT_CL_MEM_POLYGONS,
	RT_CL_MEM_VERTICES,
	RT_CL_MEM_V_NORMALS,
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
}				t_cl_mem_types;

/*
** Kernel types
*/

# define KERNEL_ALL 0b1111111111111111

# define KERNEL_GENERATE_RAYS (1 << 0)
# define KERNEL_FIND_INTERSECTIONS (1 << 1)
# define KERNEL_TEXTURE_SHADE (1 << 2)
# define KERNEL_MATERIAL_SHADE (1 << 3)
# define KERNEL_SKYBOX_SHADE (1 << 4)

/*
**	Renderers params
*/

# define RENDER_ALWAYS 0b1111111111111111

# define RENDER_NOTHING 0

# define RENDER_RAYTRACE (1 << 0)
# define RENDER_PATHTRACE (1 << 1)
# define RENDER_RAYMARCH (1 << 2)
# define RENDER_MESH (1 << 3)
# define RENDER_BACKFACE_CULLING (1 << 4)
# define RENDER_OBJECTS (1 << 5)
# define RENDER_MESH_VTEXTURES (1 << 6)
# define RENDER_TEXTURES (1 << 7)
# define RENDER_ANTI_ALIASING (1 << 8)

# define RENDER_DEFAULT RENDER_RAYTRACE | /*RENDER_OBJECTS |*/ RENDER_TEXTURES | RENDER_MESH /*| RENDER_BACKFACE_CULLING*/

# define RT_DEFAULT_MEM_FLAG (CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR)
# define RT_MEM_RW_FLAG (CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR)

/*
**	OpenCL host constants
**
**  -> Раскомментив строчку OPENCL_DEBUG_KERNEL_NUM можно запустить мало кернелов,
** 	например, для проверки правильной передачи данных на видеокарту или того,
** 	как работают какие-либо функции.
**
**  [при OPENCL_RELEASE_KERNEL_NUM, т.е. на ~3-ех миллионах кернелов,
** 	случайный printf в кернеле приводит к намертво зависшему компу]
*/

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