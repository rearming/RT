#include "rt.h"
#include "rt_math_utils.h"
#include "rt_colors.h"

t_material		rt_default_material(void)
{
	t_material	material;
	material.ambient = (cl_float3){{0.2, 0.2, 0.2}};
	material.diffuse = get_float3_color(COL_DARK_GREY);
	material.specular = (cl_float3){{0, 0, 0}};
	material.emission_color = (cl_float3){{0, 0, 0}};
	material.emission_power = 0;
	material.phong_exp = 0;
	material.smoothness = 0;
	material.transmittance = 0;
	material.refraction = 0;
	material.texture_number = NOT_SET;
	return (material);
}

t_material		rt_convert_obj_material(t_obj_material obj_material)
{
	t_material		material;

	material.ambient = obj_material.ambient;
	material.diffuse = obj_material.diffuse;
	material.specular = obj_material.specular;
	material.emission_color = obj_material.emission;
	material.emission_power = float3_color_power(material.emission_color) > 0 ? 1 : 0;
	material.smoothness = obj_material.phong_exp * 21.f;
	material.phong_exp = obj_material.phong_exp * 21.f;
	material.transmittance = obj_material.transmittance;
	material.refraction = obj_material.refraction;
	material.texture_number = NOT_SET;
	return (material);
}
