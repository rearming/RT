#ifndef RT_OPENCL_PARAMS_DEFINES_H
# define RT_OPENCL_PARAMS_DEFINES_H

# define OPENCL_KERNEL_NAME "rt_main"

/*
**	Renderers params
*/

# define REND_RAYTRACE (1 << 0)
# define REND_PATHTRACE (1 << 1)
# define REND_RAYMARCH (1 << 2)
# define REND_MESH (1 << 3)
# define REND_BACKFACE_CULLING (1 << 4)

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
" -I ./sources/OpenCL_kernel_code " \
" -I ./sources/OpenCL_kernel_code/light_computing " \
" -I ./sources/OpenCL_kernel_code/mesh_render " \
" -I ./sources/OpenCL_kernel_code/object_intersections " \
" -I ./sources/OpenCL_kernel_code/pathtrace_algo "

#  define OPENCL_DEFINES \
" -D PATHTRACE " \
" -D RAYTRACE " \
" -D MESH_RENDER " \
" -D BACKFACE_CULLING "

#  define OPENCL_COMPILE_OPTIONS \
OPENCL_INCLUDE_DIRS \
OPENCL_DEFINES
# endif

# ifdef __APPLE__
#  define OPENCL_APPLE_DEFINE "#define __APPLE__\n\n"
# else
#  define OPENCL_APPLE_DEFINE "\n"
# endif

#endif