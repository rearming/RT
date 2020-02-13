#include "rt.h"
//подумать про варианты когда материал парсит или спекюлар заданы как массив элементов
const int		ft_check1(const char *param)
{
	if (ft_strequ(param, "pos"))
		return (POS);
	else if (ft_strequ(param, "rotation"))
		return (ROTATION);
	else if (ft_strequ(param, "direction"))
		return (DIRECTION);
	else if (ft_strequ(param, "color"))
		return (COLOR);
	else if (ft_strequ(param, "normal"))
		return (NORMAL);
	else if (ft_strequ(param, "texture position"))
		return (TEXTURE_POS);
	return (-1);
}

const int		ft_check2(const char *param)
{
	if (ft_strequ(param, "ambient"))
		return (AMBIENCE);
	else if (ft_strequ(param, "diffuse"))
		return (DIFFUSE);
	else if (ft_strequ(param, "specular"))
		return (SPECULAR);
	else if (ft_strequ(param, "emission color"))
		return (EMISSION_COLOR);
	return (-1);
}

const int 		ft_check3(const char *param)
{
	if (ft_strequ(param, "light"))
		return LIGHT;
	else if (ft_strequ(param, "ambient"))
		return AMBIENT;
	else if (ft_strequ(param, "point"))
		return POINT;
	return (-1);
}

const int		ft_check4()
{
	if (ft_strequ(param, "object"))
		return OBJECT;
	else if (ft_strequ(param, "sphere"))
		return SPHERE;
	else if (ft_strequ(param, "cone"))
		return CONE;
	else if (ft_strequ(param, "cylinder"))
		return CYLINDER;
	else if (ft_strequ(param, "plane"))
		return PLANE;
	return (-1);
}

// 1 - coord_checker traditional, 2 - material_checker traditional, 3 - light  4 - object
int 			ft_type_of_array(int *type_of_element, const char *param)
{
	int tmp_type; //может просто чекать если array type is number || array type is object

	tmp_type = ft_check1(param);
	if (tmp_type != -1)
	{
		type_of_element = tmp_type;
		return (1);
	}
	tmp_type = ft_check2(param);
	if (tmp_type != -1)
	{
		type_of_element = tmp_type;
		return (2);
	}
	tmp_type = ft_check3(param);
	if (tmp_type != -1)
	{
		type_of_element = tmp_type;
		return (3);
	}
	tmp_type = ft_check4(param);
	if (tmp_type != -1)
	{
		type_of_element = tmp_type;
		return (4);
	}
	return (-1);
}