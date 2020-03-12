#ifndef RT_DEFINES_H
# define RT_DEFINES_H

//# define DEBUG_LOADING 1

/*
**	Code constants
*/

# define VALID_ARGS_NUM 2
# define EXIT_SUCCESS 0

# define RT_OBJLOADER_NOFLAGS 0

#define TEXTURES_FOLDER "./assets/textures/"
#define SKYBOX_NUM	0
/*
**	Window params
*/

# define WIN_TITLE "Dota 5"

# ifdef __APPLE__
#  define WIN_WIDTH 1900
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
# define COL_RED 0xFFFF0000
# define COL_GREEN 0xFF00FF00
# define COL_BLUE 0xFF0000FF
# define COL_YELLOW 0xFFFFFF00
# define COL_WHITE 0xFFFFFFFF
# define COL_GREY 0xFF3A3635
# define COL_BLACK 0xFF000000
# define COL_PURPLE 0xFF7830E0
# define COL_MAGNETA 0xFFE2007A

# define COL_LIGHT_RED 0xFFff4d4d
# define COL_LIGHT_PURPLE 0xFF9C6AE4
# define COL_LIGHT_GREEN 0xFFb3ff66
# define COL_LIGHT_BLUE 0xFF80ddff
# define COL_LIGHT_GREY 0xFFB9D5E2

# define COL_DARK_GREY 0xFF4E4959
# define COL_DARK_RED 0xFFb30f0f
# define COL_DARK_PURPLE 0xFF4D1E91
# define COL_DARK_GREEN 0xFF408000
# define COL_DARK_BLUE 0xFF000080

# define COL_GOLD 0xFFffd700
# define COL_BG COL_GREY

/*
**	Development
*/

# define RT_UNUSED(arg) (void)arg

/*
**	Objects and materials
*/

# define MAX_SMOOTHNESS 10000 //todo сделать в диапазоне [0, 1000]
# define MAX_TRANSMITTANCE 1

/*
**	Other ?
*/

#define RAYS_CHUNK_SIZE 9
#ifndef M_PI
# define M_PI 3.14159265358979323846f
#endif

# define M_PI_180 (M_PI / 180.0f)
# define NOT_SET (-1)

# ifndef UINT_MAX
#  define UINT_MAX 4294967295
# endif

# define KD_TREE_MAX_HEIGHT 23 // ~log2(10kk)

/*
**	Camera moving
*/

# define MOVE_SPEED (0.2)
# define SIDE_MOVE_SPEED (0.1)
# define FLY_SPEED 0.2

# ifdef __APPLE__
#  define ROTATION_SPEED 0.025
# else
#  define ROTATION_SPEED 0.25
# endif



#endif
