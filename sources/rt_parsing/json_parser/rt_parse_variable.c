#include "rt.h"

static void	add_param_f(int *checker, json_t *value, float *vector, int type)
{
	if ((*checker = ft_check_if_exist(*checker, type)) != -1)
		*vector = (float)json_real_value(value);
	else
		rt_raise_error("error variable parameter");
}

static void	add_param_i(int *checker, json_t *value, int *vector, int type)
{
	if ((*checker = ft_check_if_exist(*checker, type)) != -1)
		*vector = json_integer_value(value);
	else
		rt_raise_error("error variable parameter");
}

void		parse_variable(t_tmp *tmp, const char *key, json_t *value)
{
	if (ft_strequ(key, "type"))
		add_param_i(&tmp->coord_checker, value, &tmp->type, TYPE);
	else if (ft_strequ(key, "intensity"))
		add_param_f(&tmp->coord_checker, value, &tmp->intensity, INTENSITY);
	else if (ft_strequ(key, "radius"))
		add_param_f(&tmp->coord_checker, value, &tmp->radius, RADIUS);
	else if (ft_strequ(key, "angle"))
		add_param_f(&tmp->coord_checker, value, &tmp->angle, ANGLE);
	else if (ft_strequ(key, "len"))
		add_param_f(&tmp->coord_checker, value, &tmp->len, LEN);
	else if (ft_strequ(key, "phong exp"))
		add_param_f(&tmp->material_checker, value, &tmp->phong_exp, PHONG_EXP);
	else if (ft_strequ(key, "smoothness"))
		add_param_f(&tmp->material_checker, value, &tmp->smoothness, SMOOTHNESS);
	else if (ft_strequ(key, "transmittance"))
		add_param_f(&tmp->material_checker, value, &tmp->transmittance, TRANSMITTANCE);
	else if (ft_strequ(key, "refraction"))
		add_param_f(&tmp->material_checker, value, &tmp->refraction, REFRACTION);
	else if (ft_strequ(key, "emission_power"))
		add_param_f(&tmp->material_checker, value, &tmp->emission_power, EMISSION_POWER);
	else if (ft_strequ(key, "specular_texture"))
		add_param_f(&tmp->coord_checker, value, &tmp->specular_texture, SPECULAR_TEXTURE);
	else
		rt_raise_error(ERR_PARSING_WRONG_OBJECT_PARAMS);
}
