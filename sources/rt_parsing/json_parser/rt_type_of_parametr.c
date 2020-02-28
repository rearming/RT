#include "rt.h"

static int	ft_check_material(const char *param, int *type_of_element)
{
	if (ft_strequ(param, "ambient"))
		*type_of_element = AMBIENCE;
	else if (ft_strequ(param, "diffuse"))
		*type_of_element = DIFFUSE;
	else if (ft_strequ(param, "specular"))
		*type_of_element = SPECULAR;
	else if (ft_strequ(param, "emission color"))
		*type_of_element = EMISSION_COLOR;
	else if (ft_strequ(param, "texture position"))
		*type_of_element = TEXTURE_POS;
	return (*type_of_element != -1) ? 1 : -1;
}

static int	ft_check(const char *param, int *type_of_element)
{
	if (ft_strequ(param, "rotation"))
		*type_of_element = ROTATION;
	else if (ft_strequ(param, "pos"))
		*type_of_element = POS;
	else if (ft_strequ(param, "direction"))
		*type_of_element = DIRECTION;
	else if (ft_strequ(param, "color"))
		*type_of_element = COLOR;
	else if (ft_strequ(param, "normal"))
		*type_of_element = NORMAL;
	else if (ft_strequ(param, "axis"))
		*type_of_element = AXIS;
	else if (ft_strequ(param, "center"))
		*type_of_element = CENTER;
	else if (ft_strequ(param, "vmin"))
		*type_of_element = VMIN;
	else if (ft_strequ(param, "vmax"))
		*type_of_element = VMAX;
	return (*type_of_element != -1) ? 1 :
	ft_check_material(param, type_of_element);
}

int			ft_type_of_array(int *type_of_element,
		const char *param, int structure_type)
{
	if (ft_strequ(param, "objects"))
		*type_of_element = OBJECT;
	if (ft_strequ(param, "light"))
		*type_of_element = LIGHT;
	if (structure_type == LIGHT)
	{
		if (ft_strequ(param, "ambient"))
			*type_of_element = AMBIENT;
		else if (ft_strequ(param, "point"))
			*type_of_element = POINT;
		else if (ft_strequ(param, "directional"))
			*type_of_element = DIRECTIONAL;
	}
	if (structure_type == OBJECT)
	{
		if (ft_strequ(param, "sphere"))
			*type_of_element = SPHERE;
		else if (ft_strequ(param, "cone"))
			*type_of_element = CONE;
		else if (ft_strequ(param, "cylinder"))
			*type_of_element = CYLINDER;
		else if (ft_strequ(param, "plane"))
			*type_of_element = PLANE;
		else if (ft_strequ(param, "AABB"))
			*type_of_element = AABB;
		else if (ft_strequ(param, "triangle"))
			*type_of_element = TRIANGLE;
		else if (ft_strequ(param, "paraboloid"))
			*type_of_element = PARABOLOID;
		else if (ft_strequ(param, "ellipsoid"))
			*type_of_element = ELLIPSOID;
	}
	return (*type_of_element != -1) ? 2 : (ft_check(param, type_of_element));
}

int			ft_type_of_structure(const char *param)
{
	if (ft_strequ(param, "object"))
		return (OBJECT);
	else if (ft_strequ(param, "light"))
		return (LIGHT);
	else if (ft_strequ(param, "camera"))
		return (CAMERA);
	else if (ft_strequ(param, "material"))
		return (MATERIAL);
	return (-1);
}
