#include "rt.h"

float		ft_minf(float a, float b)
{
	return (a < b ? a : b);
}

float		ft_maxf(float a, float b)
{
	return (a < b ? b : a);
}

float		ft_clampf(float value, float lower, float upper)
{
	return ft_minf(upper, ft_maxf(lower, value));
}

float		ft_saturate(float value)
{
	return (ft_clampf(value, 0.f, 1.f));
}
