#include "rt.h"
#include "rt_parsing.h"

static float	parse_f(json_t *value)
{
	return (json_is_integer(value) ?
	((float)json_integer_value(value)) : ((float)json_real_value(value)));
}

static void		parse_variable_material2(t_tmp *tmp, const char *key,
		json_t *value)
{
	if (ft_strequ(key, "refraction"))
	{
		check_duplicated(tmp->checker, REFRACTION);
		tmp->refraction = parse_f(value);
	}
	else if (ft_strequ(key, "emission power"))
	{
		check_duplicated(tmp->checker, EMISSION_POWER);
		tmp->emission_power = parse_f(value);
	}
	else if (ft_strequ(key, "specular texture"))
	{
		check_duplicated(tmp->checker, SPECULAR_TEXTURE);
		tmp->specular_texture = parse_f(value);
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_PARAM);
}

static void		parse_variable_material1(t_tmp *tmp, const char *key,
		json_t *value)
{
	if (ft_strequ(key, "phong exp"))
	{
		check_duplicated(tmp->checker, PHONG_EXP);
		tmp->phong_exp = parse_f(value);
	}
	else if (ft_strequ(key, "smoothness"))
	{
		check_duplicated(tmp->checker, SMOOTHNESS);
		tmp->smoothness = parse_f(value);
	}
	else if (ft_strequ(key, "transmittance"))
	{
		check_duplicated(tmp->checker, TRANSMITTANCE);
		tmp->transmittance = parse_f(value);
	}
	else
		parse_variable_material2(tmp, key, value);
}

static void		parse_variable_params(t_tmp *tmp, const char *key,
		json_t *value)
{
	if (ft_strequ(key, "distance"))
	{
		check_duplicated(tmp->checker, DISTANCE);
		tmp->distance = parse_f(value);
	}
	else if (ft_strequ(key, "radius"))
	{
		check_duplicated(tmp->checker, RADIUS);
		tmp->radius = parse_f(value);
	}
	else if (ft_strequ(key, "angle"))
	{
		check_duplicated(tmp->checker, ANGLE);
		tmp->angle = parse_f(value);
	}
	else if (ft_strequ(key, "len"))
	{
		check_duplicated(tmp->checker, LEN);
		tmp->len = parse_f(value);
	}
	else
		parse_variable_material1(tmp, key, value);
}

void			parse_variable(t_tmp *tmp, const char *key, json_t *value)
{
	if (ft_strequ(key, "type"))
	{
		check_duplicated(tmp->checker, TYPE);
		tmp->type = json_integer_value(value);
	}
	else if (ft_strequ(key, "intensity"))
	{
		check_duplicated(tmp->checker, INTENSITY);
		tmp->intensity = parse_f(value);
	}
	else
		parse_variable_params(tmp, key, value);
}
