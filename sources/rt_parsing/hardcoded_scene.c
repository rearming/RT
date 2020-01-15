#include "rt.h"

static	t_object	*rt_get_objects(int *out_obj_nbr)
{
	const int	objects_nbr = 1;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);
	objects[0] = (t_object){.type = SPHERE,
			(t_material){.color = {COL_RED}, .specular = 42, .albedo = 0.5},
			.center = (cl_float3){{0, -1, 2}},
			.radius = 0.5};
	return (objects);
}

static t_light		*rt_get_lights(int *out_lights_nbr)
{
	const int	lights_nbr = 2;
	t_light		*lights;

	*out_lights_nbr = lights_nbr;
	lights = rt_safe_malloc(sizeof(t_light) * lights_nbr);
	lights[0] = (t_light){.pos = {{0, 0.5, 0}}, .color = {COL_WHITE}, .type = POINT, .intensity = 0.9};
	lights[1] = (t_light){.color = {COL_WHITE}, .type = AMBIENT, .intensity = 0.3};
	return (lights);
}

t_scene		get_hardcoded_scene(void)
{
	t_scene		scene;

	scene.camera = (t_camera)
	{
		.pos = (cl_float3){{0, 0, -3}},
		.rotation = (cl_float3){{0, 0, 0}},
		.viewport_distance = 1,
		.viewport_width = WIN_RATIO < 1 ? D_I_MAZOHIN : 1,
		.viewport_height = WIN_RATIO > 1 ? D_E_KARMATSKIY : 1
	};
	scene.objects = rt_get_objects(&scene.obj_nbr);
	scene.lights = rt_get_lights(&scene.lights_nbr);
	return (scene);
}
