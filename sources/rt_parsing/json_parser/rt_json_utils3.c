#include "rt.h"

void	check_duplicated(bool *checker, int number)
{
	if (checker[number] == true)
		rt_raise_error(ERR_PARSING_DUPLICATED_PARAM);
	else
		checker[number] = true;
}

char	*object_name(int type)
{
	if (type == SPHERE)
		return ("Sphere");
	if (type == CONE)
		return ("Cone");
	if (type == CYLINDER)
		return ("Cylinder");
	if (type == PLANE)
		return ("Plane");
	if (type == AABB)
		return ("AABB");
	if (type == TRIANGLE)
		return ("Triangle");
	if (type == PARABOLOID)
		return ("Paraboloid");
	if (type == ELLIPSOID)
		return ("Ellipsoid");
	return (NULL);
}
