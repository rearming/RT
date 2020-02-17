#ifndef RT_PARSER_DEFINES_H
# define RT_PARSER_DEFINES_H

// может быть сделать чекер строкой и проверять есть ли там уже такая буква:?
// нормировать все оси, нормали и т.п. и проверить все значения по умолчанию

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
#define CENTER 6
#define NORMAL 7
#define RADIUS 8
#define LEN 10
#define ANGLE 9
#define MATERIAL 22

//material
#define SPECULAR 13
#define AMBIENCE 11
#define DIFFUSE 12
#define PHONG_EXP 14
#define SMOOTHNESS 15
#define TRANSMITTANCE 16
#define REFRACTION 17
#define EMISSION_POWER 18
#define SPECULAR_TEXTURE 19
#define TEXTURE 20
#define TEXTURE_POS 21

#endif