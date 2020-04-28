#ifndef RT_DEFINES_H
# define RT_DEFINES_H

//# define DEBUG_LOADING 1

/*
**	Code constants
*/

# define MIN_ARGS_NUM 2
# define EXIT_SUCCESS 0

# define RT_OBJLOADER_NOFLAGS 0

#define TEXTURES_FOLDER "./assets/textures/"
#define SKYBOX_NUM	0

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

# define M_PI_180 (M_PI / 180)
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

# define MAX_FOCAL_DISTANCE 50.0f

# ifdef __APPLE__
#  define ROTATION_SPEED 0.025
# else
#  define ROTATION_SPEED 0.05
# endif

#endif
