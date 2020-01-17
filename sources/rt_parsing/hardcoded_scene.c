#include "rt.h"

static	t_object	*rt_get_objects(int *out_obj_nbr)
{
	const int	objects_nbr = 2;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);
	objects[0] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_RED), .specular = (cl_float3){{0, 0, 0}}},
			.center = (cl_float3){{0, 2, 0}},
			.radius = 1};
	objects[1] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_BLUE), .specular = (cl_float3){{0, 0, 0}}},
			.center = (cl_float3) {{0, -4, 0}},
			.normal = (cl_float3){{0, 1, 0}}};
	return (objects);
}

static t_light		*rt_get_lights(int *out_lights_nbr)
{
	const int	lights_nbr = 2;
	t_light		*lights;

	*out_lights_nbr = lights_nbr;
	lights = rt_safe_malloc(sizeof(t_light) * lights_nbr);
	lights[0] = (t_light){.color = get_float3_color(COL_WHITE), .type = AMBIENT, .intensity = 0.2};
	lights[1] = (t_light){.pos = {{-1, 0.5, 2}}, .color = get_float3_color(COL_WHITE), .type = POINT, .intensity = 0.7};
//	lights[2] = (t_light){.pos = {{1, 0.5, 2}}, .color = {COL_GREEN}, .type = POINT, .intensity = 0.9};
	return (lights);
}

t_scene		get_hardcoded_scene(void)
{
	t_scene		scene;

	scene.camera = (t_camera)
	{
		.pos = (cl_float3){{-3.8, 0, -2.25}},
		.rotation = (cl_float3){{10, 58, 0}},
		.viewport_distance = 1,
		.viewport_width = WIN_RATIO < 1 ? D_I_MAZOHIN : 1,
		.viewport_height = WIN_RATIO > 1 ? D_E_KARMATSKIY : 1
	};
	scene.objects = rt_get_objects(&scene.obj_nbr);
	scene.lights = rt_get_lights(&scene.lights_nbr);
	return (scene);
}
