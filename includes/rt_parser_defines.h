#ifndef RT_PARSER_DEFINES_H
# define RT_PARSER_DEFINES_H

// может быть сделать чекер строкой и проверять есть ли там уже такая буква:?
#define CAMERA 10
#define LIGHT 20
#define OBJECT 30

#define SPHERE 1
#define CONE 2
#define CYLINDER 3
#define PLANE 4

#define AMBIENT 1 		// intensity, color
#define POINT 2			// intensity, color, pos
#define DIRECTIONAL 3 	// intensity, color, 	, dir
#define PARALLEL 4		// intensity, color, pos, dir

//check camera
#define POS 2			//obj for obj
#define ROTATION 3

//check light
#define TYPE 0		//obj, lyght
#define INTENSITY 1
#define DIRECTION 4
#define COLOR 5

//check objects

//position attributes
#define NORMAL 6
#define RADIUS 7
#define LEN 9
#define ANGLE 8
#define MATERIAL 21

//material
#define SPECULAR 12
#define AMBIENCE 10
#define DIFFUSE 11
#define PHONG_EXP 13
#define SMOOTHNESS 14
#define TRANSMITTANCE 15
#define REFRACTION 16
#define EMISSION_POWER 17
#define SPECULAR_TEXTURE 18
#define TEXTURE 19
#define TEXTURE_POS 20

#endif