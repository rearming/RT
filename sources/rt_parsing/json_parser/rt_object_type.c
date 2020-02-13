#include "rt.h"

int		ft_type_of_structure(const char *param)
{
	if (ft_strequ(param, "object"))
		return (OBJECT);
	else if (ft_strequ(param, "light"))
		return (LIGHT);
	else if (ft_strequ(param, "camera"))
		return (CAMERA);
	else if (ft_strequ(key, "material"))
		return (MATERIAL);
	return (-1);
}

int		type_of_object(const char *param, int type)
{
	if (type == OBJECT)
	{
		if (ft_strequ(param, "sphere"))
			return (SPHERE);
		else if (ft_strequ(param, "cone"))
			return (CONE);
		else if (ft_strequ(param, "cylinder"))
			return (CYLINDER);
		else if (ft_strequ(param, "plane"))
			return (PLANE);
	}
	if (type == LIGHT)
	{
		if (ft_strequ(param, "ambient"))
			return (AMBIENT);
		else if (ft_strequ(param, "point"))
			return (POINT);
	}
	return (-1);
}