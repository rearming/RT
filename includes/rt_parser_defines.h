#ifndef RT_PARSER_DEFINES_H
# define RT_PARSER_DEFINES_H

# define CAMERA 10
# define LIGHT 20
# define OBJECT 30
# define RENDER_PARAMS 40
# define SCENE_PARAMS 50

# define PATHTRACE 1
# define RAYTRACE 2
# define MESH 3
# define TEXTURES 4
# define SKYBOX 5

# define SPHERE 1
# define CONE 4
# define CYLINDER 3
# define PLANE 2
# define AABB 6
# define TRIANGLE 5
# define PARABOLOID 7
# define ELLIPSOID 8
# define BOX 9
# define CAPSULE 10
# define TORUS 11
# define ELLIPSOID_RAYMARCH 12
# define TORUS_CAPPED 13
# define HEX_PRISM 14
# define ROUND_CONE 15
# define TEST_OBJECT 16

#define AMBIENT 1 		// intensity, color
#define POINT 2			// intensity, color, pos
#define DIRECTIONAL 3 	// intensity, color, 	, dir
#define PARALLEL 4		// intensity, color, pos, dir

//check camera
#define POS 2
#define ROTATION 3

//check light
# define TYPE 0		//obj, light
# define INTENSITY 1
# define DIRECTION 4
# define COLOR 5

//check objects

//position attributes
# define CENTER 6
# define NORMAL 7
# define AXIS 8
# define VMIN 9
# define VMAX 10
# define RADIUS 11
# define LEN 12
# define ANGLE 13
# define DISTANCE 14
# define MATERIAL 15

//material
# define SPECULAR 16
# define AMBIENCE 17
# define DIFFUSE 18
# define PHONG_EXP 19
# define SMOOTHNESS 20
# define TRANSMITTANCE 21
# define REFRACTION 22
# define EMISSION_COLOR 23
# define EMISSION_POWER 24
# define SPECULAR_TEXTURE 25
# define TEXTURE 26
# define TEXTURE_POS 27
# define TEXTURE_PBR 28
# define TEXTURE_NORMAL 29
# define TEXTURE_PBR_INDEX 30

//position attributes
# define ALFA_ANGLE 31
# define BETA_ANGLE 32
# define GAMMA_ANGLE 33
# define COMPLICATED 34
# define COMPLICATED_INDEX 35
# define SIZE 36
# define RADIUS_RING 37
# define RADIUS_2 38
# define PARAM_0 39
# define PARAM_1 40

//scene parameters
# define EXPOSURE 41
# define GAMMA 42

# define DIRECTORY 43
# define FILE_NAME 44

#endif