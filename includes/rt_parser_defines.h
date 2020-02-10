#ifndef RT_PARSER_DEFINES_H
# define RT_PARSER_DEFINES_H

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
#define POS 2
#define ROTATION 30

//check light
#define TYPE 10
#define INTENSITY 100
#define DIRECTION 1000
#define COLOR 10000

//check objects

//position attributes
#define NORMAL 20
#define RADIUS 200
#define LEN 300
#define ANGLE 100000

//material
#define SPECULARITY 2000
#define AMBIENCE
#define DIFFUSE
#define PHONG_EXP
#define SMOTHNESS
#define TRANSMITTANCE
#define REFRACTION
#define EMISSION_COLOR
#define SPECULAR_TEXTURE
#define TEXTURE 20000
#define TEXTURE_POS 200000


#endif