#include "rt.h"
#include "rt_load_obj_files.h"

t_obj_material	rt_get_obj_material(tinyobj_material_t *material)
{
	t_obj_material	obj_material;

	obj_material.ambient = (cl_float3){{
		material->ambient[0],
		material->ambient[1],
		material->ambient[2]}};
	obj_material.diffuse = (cl_float3){{
		material->diffuse[0],
		material->diffuse[1],
		material->diffuse[2]}};
	obj_material.specular = (cl_float3){{
		material->specular[0],
		material->specular[1],
		material->specular[2]}};
	obj_material.emission = (cl_float3){{
		material->emission[0],
		material->emission[1],
		material->emission[2]}};
	obj_material.phong_exp = material->shininess;
	obj_material.transmittance = 1 - material->dissolve;
	obj_material.refraction = material->ior;
	return (obj_material);
}
