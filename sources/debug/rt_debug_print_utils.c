#include "rt.h"
#include "rt_debug.h"

void		rt_print_clfloat3(cl_float3 vec, const char *definition)
{
	ft_printf("%s: x: [%.2f], y: [%.2f], z: [%.2f]\n", definition, vec.x, vec.y, vec.z);
}

void		rt_print_float3_color(cl_float3 color, const char *definition)
{
	ft_printf("%s: r: [%.2f], g: [%.2f], b: [%.2f]\n", definition, color.x, color.y, color.z);
}

void		rt_print_material(const t_material *material)
{
	ft_printf("material:\n");
	rt_print_float3_color(material->diffuse, "diffuse");
	rt_print_float3_color(material->specular, "specular");
	ft_printf("smoothness: [%.2f]\n", material->smoothness);
	ft_printf("phong exponent: [%.2f]\n", material->phong_exp);
	ft_printf("refraction: [%.2f]\n", material->refraction);
	ft_printf("transmittance: [%.2f]\n", material->transmittance);
	if (material->emission_power > 0)
	{
		ft_printf("emission_power: [%f]\n", material->emission_power);
		rt_print_float3_color(material->emission_color, "emission color");
	}
	/// потом может будут нужны texture_number и texture_position
}
