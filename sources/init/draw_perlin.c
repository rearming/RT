#include "rt.h"

static unsigned int		colorf(float x)
{
	unsigned char	b;

	b = (unsigned char)(x * 255.0f);
	return ((unsigned int)(b | (b << 8) | (b << 16)));
}

float		geo_clamp(float x, float min, float max)
{
	if (x < min)
		return (min);
	return ((x > max) ? max : x);
}

cl_float2		geo_smoothstep(cl_float2 a, cl_float2 b, cl_float2 x)
{
	cl_float2	t;

	t = (cl_float2){{
							geo_clamp((x.x - a.x) / (b.x - a.x), 0.0f, 1.0f),
							geo_clamp((x.y - a.y) / (b.x - a.y), 0.0f, 1.0f),
					}};
	return ((cl_float2) {{t.x * t.x * (3.0f - 2.0f * t.x),
								 t.y * t.y * (3.0f - 2.0f * t.y)}});
}

cl_float2	geo_fract_v2f(cl_float2 v)
{
	return ((cl_float2){{v.x - floor(v.x), v.y - floor(v.y)}});
}

float		geo_mix(float a, float b, float pc)
{
	return (a * (1.0f - pc) + (b * pc));
}

float	geo_dotv2f(cl_float2 a, cl_float2 b)
{
	return (a.x * b.x + a.y * b.y);
}

float	geo_fract(float x)
{
	return (x - floorf(x));
}

static float		r(cl_float2 n)
{
	return (geo_fract(cosf(geo_dotv2f(n, (cl_float2) {{36.26f, 73.12f}})) * 354.63f));
}

cl_float2		geo_addv2f(cl_float2 a, cl_float2 b)
{
	return ((cl_float2){a.x + b.x, a.y + b.y});
}

static float		noise(float x, float y)
{
	cl_float2 	fn;
	cl_float2	sn;
	float		h1;
	float		h2;

	fn = (cl_float2) {{floorf(x), floorf(y)}};
	sn = geo_smoothstep(
			(cl_float2) {{0.0f, 0.0f}},
			(cl_float2) {{1.0f, 1.0f}},
			geo_fract_v2f((cl_float2){{x,y}}));
	h1 = geo_mix(r(fn), r(geo_addv2f(
			fn,
			(cl_float2) {{1.0f, 0.0f}})), sn.x);
	h2 = geo_mix(r((cl_float2) {{fn.x, fn.y + 1.0f}}),
				 r((cl_float2) {{fn.x + 1.0f, fn.y + 1.0f}}), sn.x);
	return (geo_mix(h1, h2, sn.y));
}


float				geo_perlin(float x, float y)
{
	float	total;

	total = noise(x /32.0f * 0.5875f,  y/32.0f * 0.5875f) +
			noise(x / 16.0f, y / 16.0f) * 0.2f +
			noise(x * 0.125f, y * 0.125f) * 0.1f +
			noise(x / 4.0f, y / 4.0f) * 0.05f +
			noise(x / 2.0f, y / 2.0f) * 0.025f +
			noise(x, y) * 0.0125f;
	return (total);
}

void	draw_perlin()
{
	int x;
	int y;
	//unsigned int	*pixels;

	//pixels = g_textures.texture_list;
	x = g_textures.texture_info[0].width;
	while (x--)
	{
		y = g_textures.texture_info[0].height;
		while (y--)
		{
			g_textures.texture_list[y * g_textures.texture_info[0].width + x] = colorf(
					geo_clamp(geo_perlin((float)x, (float)y), 0.0f, 1.0f));
		}
	}
}
