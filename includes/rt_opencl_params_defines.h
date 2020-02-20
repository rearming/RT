#ifndef RT_OPENCL_PARAMS_DEFINES_H
# define RT_OPENCL_PARAMS_DEFINES_H

# define OPENCL_KERNEL_NAME "rt_main"

/*
**	Renderers params
*/

# define RENDER_ALWAYS 0b1111111111111111

# define RENDER_RAYTRACE (1 << 0)
# define RENDER_PATHTRACE (1 << 1)
# define RENDER_RAYMARCH (1 << 2)
# define RENDER_MESH (1 << 3)
# define RENDER_BACKFACE_CULLING (1 << 4)
# define RENDER_OBJECTS (1 << 5)
# define RENDER_MESH_VTEXTURES (1 << 6)
# define RENDER_TEXTURES (1 << 7)
# define RENDER_SKYBOX (1 << 8)

# define RENDER_DEFAULT RENDER_RAYTRACE | RENDER_OBJECTS | RENDER_TEXTURES | RENDER_MESH | RENDER_BACKFACE_CULLING

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
" -I ./sources/kernel/texture_formulas"



////" -I ./sources/OpenCL_kernel_code " \
//" -I ./sources/OpenCL_kernel_code/light_computing " \
//" -I ./sources/OpenCL_kernel_code/mesh_render " \
//" -I ./sources/OpenCL_kernel_code/object_intersections " \
///*" -I ./sources/OpenCL_kernel_code/object_intersections/more_difficult_object " */\
//" -I ./sources/OpenCL_kernel_code/pathtrace_algo " \
//" -I ./sources/OpenCL_kernel_code/texture_formulas"
# endif

# ifdef __APPLE__
#  define OPENCL_APPLE_DEFINE "#define __APPLE__\n\n"
# else
#  define OPENCL_APPLE_DEFINE "\n"
# endif

#endif