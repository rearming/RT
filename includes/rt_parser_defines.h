#ifndef RT_PARSER_DEFINES_H
# define RT_PARSER_DEFINES_H

// может быть сделать чекер строкой и проверять есть ли там уже такая буква:?
#define CAMERA 1
#define LIGHT 10
#define OBJECT 1000

#define SPHERE 1
#define CONE 2
#define CYLINDER 3
#define PLANE 4

#define AMBIENT 1 		// intensity, color
#define POINT 2			// intensity, color, pos
#define DIRECTIONAL 3 	// intensity, color, 	, dir
#define PARALLEL 4		// intensity, color, pos, dir

//check camera
#define POS 1			//obj for obj
#define ROTATION 20

//check light
#define TYPE 10		//obj, lyght
#define INTENSITY 100
#define DIRECTION 1000
#define COLOR 100000

//check objects

//position attributes
#define NORMAL 100
#define RADIUS 1000
#define LEN 2000
#define ANGLE 10000
#define MATERIAL 100000

//material
#define SPECULAR 2						//material_checker
#define AMBIENCE 20						//material_checker
#define DIFFUSE 200						//material_checker
#define PHONG_EXP 2000					//material_checker
#define SMOOTHNESS 20000				//material_checker
#define TRANSMITTANCE 200000			//material_checker
#define REFRACTION 2000000				//material_checker
#define EMISSION_POWER 20000000			//material_checker

#define SPECULAR_TEXTURE  1000000000	//coord_checker
#define TEXTURE 10000000				//coord_checker
#define TEXTURE_POS 100000000			//coord_checker


#endif