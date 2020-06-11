#include "rt.h"
#include "rt_debug.h"

void		rt_print_clfloat3(cl_float3 vec, const char *definition)
{
	printf("%s: x: [%f], y: [%f], z: [%f]\n", definition, vec.x, vec.y, vec.z);
}

void		rt_print_float3_color(cl_float3 color, const char *definition)
{
	printf("%s: r: [%.2f], g: [%.2f], arr: [%.2f]\n",
			definition, color.x, color.y, color.z);
}

void		rt_print_material(const t_material *material)
{
	ft_printf("material:\n");
	rt_print_float3_color(material->diffuse, "diffuse");
	rt_print_float3_color(material->specular, "specular");
	printf("smoothness: [%.2f]\n", material->smoothness);
	printf("phong exponent: [%.2f]\n", material->phong_exp);
	printf("refraction: [%.2f]\n", material->refraction);
	printf("transmittance: [%.2f]\n", material->transmittance);
	if (material->emission_power > 0)
	{
		printf("emission_power: [%f]\n", material->emission_power);
		rt_print_float3_color(material->emission_color, "emission color");
	}
}
