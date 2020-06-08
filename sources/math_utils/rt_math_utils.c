
float		rt_minf(float a, float b)
{
	return (a < b ? a : b);
}

float		rt_maxf(float a, float b)
{
	return (a < b ? b : a);
}

float		rt_clampf(float value, float lower, float upper)
{
	return (rt_minf(upper, rt_maxf(lower, value)));
}

float		rt_saturatef(float value)
{
	return (rt_clampf(value, 0.f, 1.f));
}

float		rt_lerpf(float a, float b, float t)
{
	return (a + (b - a) * t);
}
