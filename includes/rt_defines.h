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
# define OPENCL_DEFINES_STR "#define FT_OPENCL___\n #define __APPLE__\n\n"
#else
# define OPENCL_DEFINES_STR "#define FT_OPENCL___\n\n"
#endif

/*
**	Development
*/


# define DONT_COPY_MEM_AGAIN (-10)
# define CREATE_BUFFER (-32)
# define RT_UNUSED(arg) (void)arg


/*
**	Other ?
*/

# define M_PI_180 (M_PI / 180)

#endif
