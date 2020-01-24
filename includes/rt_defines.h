#ifndef RT_DEFINES_H
# define RT_DEFINES_H

/*
**	Code constants
*/

# define TRUE 1
# define FALSE 0

# define VALID_ARGS_NUM 1
# define EXIT_SUCCESS 0

# define OPENCL_KERNEL_NAME "rt_main"

# define RT_DEFAULT_MEM_FLAG (CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR)
# define RT_MEM_RW_FLAG (CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR)

/*
**	Window params
*/

# define WIN_TITLE "Dota 5"

# ifdef __APPLE__
#  define WIN_WIDTH 2550
#  define WIN_HEIGHT 1300
# else
#  define WIN_WIDTH 1920
#  define WIN_HEIGHT 1080
# endif

# define WIN_RATIO ((float)WIN_WIDTH / WIN_HEIGHT)
# define INVERSE_WIN_RATIO ((float)WIN_HEIGHT / WIN_WIDTH)
# define D_E_KARMATSKIY (INVERSE_WIN_RATIO * INVERSE_WIN_RATIO)
# define D_I_MAZOHIN (WIN_RATIO * WIN_RATIO)
# define SCALE_WIDTH 1
# define SCALE_HEIGHT 1

/*
**	Basic colors
*/

# define COL_NOT_SET (-1)
# define COL_RED 0xFF0000
# define COL_GREEN 0x00FF00
# define COL_BLUE 0x0000FF
# define COL_YELLOW 0xFFFF00
# define COL_WHITE 0xFFFFFF
# define COL_GREY 0x3A3635
# define COL_BLACK 0x0
# define COL_PURPLE 0x7830E0
# define COL_MAGNETA 0xE2007A

# define COL_LIGHT_RED 0xff4d4d
# define COL_LIGHT_PURPLE 0x9C6AE4
# define COL_LIGHT_GREEN 0xb3ff66
# define COL_LIGHT_BLUE 0x80ddff
# define COL_LIGHT_GREY 0xB9D5E2

# define COL_DARK_GREY 0x4E4959
# define COL_DARK_RED 0xb30000
# define COL_DARK_PURPLE 0x4D1E91
# define COL_DARK_GREEN 0x408000
# define COL_DARK_BLUE 0x000080

# define COL_GOLD 0xFFDB91
# define COL_BG COL_GREY

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
# define OPENCL_KERNEL_NUM OPENCL_RELEASE_KERNEL_NUM
//# define OPENCL_KERNEL_NUM OPENCL_DEBUG_KERNEL_NUM

#ifdef __APPLE__
# define OPENCL_DEFINES_STR "#define __APPLE__\n\n"
#else
# define OPENCL_DEFINES_STR "\n"
#endif

/*
**	Development
*/

# define DONT_COPY_MEM_AGAIN (-10)
# define CREATE_BUFFER (-32)
# define RT_UNUSED(arg) (void)arg


/*
**	Objects and materials
*/

# define MAX_SMOOTHNESS 10000
# define MAX_TRANSMITTANCE 1
//todo find value

/*
**	Other ?
*/

# define M_PI_180 (M_PI / 180)
# define NOT_SET (-1)

# ifndef UINT_MAX
#  define UINT_MAX 4294967295
# endif

/*
**	Camera moving
*/

# define MOVE_SPEED (0.2)
# define SIDE_MOVE_SPEED (0.1)
# define FLY_SPEED 0.2

# define ROTATION_SPEED 0.05

#endif
