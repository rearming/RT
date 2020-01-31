#include "rt.h"
#include "rt_math_utils.h"

static	t_object	*kolyan_scene(int *out_obj_nbr)
{
	const int	objects_nbr = 8;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);
	objects[0] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_GREEN), .specular = 0.9, .smoothness = MAX_SMOOTHNESS},
			.center = (cl_float3){{25, 0, 0}},
			.normal = (cl_float3){{-0.6, 0, 0}}};
	objects[1] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_GREY), .specular = 0.9, .smoothness = MAX_SMOOTHNESS},
			.center = (cl_float3){{-25, 0, 0}},
			.normal = (cl_float3){{0.6, 0, 0}}};
	objects[2] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_DARK_PURPLE), .specular = 0.9, .smoothness = MAX_SMOOTHNESS},
			.center = (cl_float3){{0, 25, 0}},
			.normal = (cl_float3){{0, -0.6, 0}}};
	objects[3] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_RED), .specular = 0.9, .smoothness = MAX_SMOOTHNESS},
			.center = (cl_float3){{0, -25, 0}},
			.normal = (cl_float3){{0, 0.6, 0}}};
	objects[4] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_BLUE), .specular = 0.9, .smoothness = MAX_SMOOTHNESS},
			.center = (cl_float3){{0, 0, 25}},
			.normal = (cl_float3){{0, 0, -0.6}}};
	objects[5] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_DARK_GREEN), .specular = 0.9, .smoothness = MAX_SMOOTHNESS},
			.center = (cl_float3){{0, 0, -25}},
			.normal = (cl_float3){{0, 0, 1}}};
	objects[6] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = 1, .smoothness = 1000},
			.center = (cl_float3){{0, 0, 0}},
			.radius = 2.5};
	objects[7] = (t_object){.type = SPHERE,
			(t_material){.emission_color = get_float3_color(COL_WHITE), .emission_power = 200},
			.center = (cl_float3){{0, 10, 0}},
			.radius = 2.5};
	return (objects);

}

static	t_object	*pathtrace_objects(int *out_obj_nbr)
{
	const int	objects_nbr = 12;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

	objects[0] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_DARK_RED), .specular = 0.7f, .smoothness = 100},
			.center = (cl_float3){{0, 2.6, 0}},
			.radius = 2.5};
	objects[1] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_GREEN), .specular = 0},
			.center = (cl_float3){{4, 1, 0}},
			.radius = 1};
	objects[2] = (t_object){.type = SPHERE, /// golden sphere
			(t_material){.albedo = get_float3_color(COL_GOLD), .specular = 1, .smoothness = 2000.f},
			.center = (cl_float3){{5, 1, 3}},
			.radius = 1};
	objects[3] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_PURPLE), .specular = 1, .smoothness = 20},
			.center = (cl_float3){{10, 2.4, 6}},
			.radius = 2.2};
	objects[4] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(0), .specular = 0,
				.emission_color = get_float3_color(COL_LIGHT_BLUE), .emission_power = 10},
			.center = (cl_float3){{-1, 0.5, 5}},
			.radius = 1};
	objects[5] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(0), .specular = 0,
				.emission_color = get_float3_color(COL_WHITE), .emission_power = 10},
			.center = (cl_float3){{7, 0, 2}},
			.radius = 0.8};
	objects[6] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = 1, .smoothness = MAX_SMOOTHNESS},
			.center = (cl_float3){{4, 2, -5}},
			.radius = 2};
	objects[7] = (t_object){.type = PLANE,
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = 0, .smoothness = 0},
			.center = (cl_float3){{0, 0, 0}},
			.normal = (cl_float3){{0, 1, 0}}};
	objects[9] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(0), .specular = 0,
					.emission_color = get_float3_color(COL_WHITE), .emission_power = 10},
			.center = (cl_float3){{700, 300, 700}},
			.radius = 100};

	objects[10] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = 1,
					.smoothness = MAX_SMOOTHNESS, .refraction = 1.5, .transmittance = 1},
			.center = (cl_float3){{15, 2.2, -6.2}},
			.radius = 2};
	objects[11] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = 1,
					.smoothness = MAX_SMOOTHNESS - 1, .refraction = 1.5, .transmittance = 1},
			.center = (cl_float3){{15, 2.6, -1.2}},
			.radius = 2};

	return (objects);
}

static	t_object	*raytrace_objects(int *out_obj_nbr)
{
	const int	objects_nbr = 5;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

	objects[0] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_GREY), .specular = 0.5},
			.center = (cl_float3){{0, 2, 0}},
			.radius = 2.5};
	objects[1] = (t_object){.type = SPHERE,
			(t_material){.albedo = get_float3_color(COL_LIGHT_GREEN), .specular = 0.3},
			.center = (cl_float3){{4, 1, 0}},
			.radius = 1};
	objects[2] = (t_object){.type = PLANE,
			(t_material){.albedo = (cl_float3){{0.8, 0.8, 0.8}}, .specular = 0.7},
			.center = (cl_float3){{0, -4, 0}},
			.normal = (cl_float3){{0, 1, 0}}};
	objects[3] = (t_object){.type = PLANE,
			(t_material){.albedo = (cl_float3){{0.8, 0.8, 0.8}}, .specular = 0},
			.center = (cl_float3) {{0, 0, -5}},
			.normal = (cl_float3){{0, 0, 1}}};

	objects[4] = (t_object){.type = PLANE,
			(t_material){.albedo = (cl_float3){{0.8, 0.8, 0.8}}, .specular = 0.7},
			.center = (cl_float3) {{-6, 0, 0}},
			.normal = (cl_float3){{1, 0, 0}}};
	return (objects);
}

static	t_object	*cornell_box(int *out_obj_nbr)
{
	const int	objects_nbr = 8;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

	objects[0] = (t_object){.type = PLANE, // bottom
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = (cl_float3){{0, 0, 0}}, .phong_exp = 0, .smoothness = 0},
			.center = (cl_float3){{0, -2.5, 0}},
			.normal = (cl_float3){{0, 1, 0}}};
	objects[1] = (t_object){.type = PLANE, // right
			(t_material){.albedo = get_float3_color(COL_GREEN), .specular = (cl_float3){{0, 0, 0}}, .phong_exp = 50, .smoothness = 0},
			.center = (cl_float3){{2.5, 0, 0}},
			.normal = (cl_float3){{1, 0, 0}}};
	objects[2] = (t_object){.type = PLANE, // left
			(t_material){.albedo = get_float3_color(COL_RED), .specular = (cl_float3){{0, 0, 0}}, .phong_exp = 0, .smoothness = 0},
			.center = (cl_float3){{-2.5, 0, 0}},
			.normal = (cl_float3){{1, 0, 0}}};
	objects[3] = (t_object){.type = PLANE, // far
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = (cl_float3){{0, 0, 0}}, .phong_exp = 40, .smoothness = 0},
			.center = (cl_float3){{0, 0, 2.5}},
			.normal = (cl_float3){{0, 0, 1}}};
	objects[4] = (t_object){.type = PLANE, // celling
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = (cl_float3){{0, 0, 0}}, .phong_exp = 0, .smoothness = 0},
			.center = (cl_float3){{0, 5.5, 0}},
			.normal = (cl_float3){{0, 1, 0}}};
	objects[5] = (t_object){.type = PLANE, // back
			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = (cl_float3){{0, 0, 0}}, .phong_exp = 0, .smoothness = 0},
			.center = (cl_float3){{0, 0, -15}},
			.normal = (cl_float3){{0, 0, 1}}};

	objects[6] = (t_object){.type = SPHERE, // light
			(t_material){.albedo = get_float3_color(0), .specular = (cl_float3){{0, 0, 0}}, .phong_exp = 0, .smoothness = 0,
				.emission_color = get_float3_color(COL_WHITE), .emission_power = 6},
			.center = (cl_float3){{0, 5.5, 0}},
			.radius = 1.f};

	objects[7] = (t_object){.type = SPHERE, // small diffuse sphere
			(t_material){.albedo = get_float3_color(COL_GREY /*COL_WHITE -> вернуть на место*/),
				.specular = (cl_float3){{0, 0, 0}}, .phong_exp = 300, .smoothness = 0},
			.center = (cl_float3){{1, -1.5f, 0}},
			.radius = 1.f};

//	objects[8] = (t_object){.type = SPHERE, // big specular sphere
//			(t_material){.albedo = get_float3_color(COL_DARK_PURPLE), .specular = {{0.7, 0.7, 0.7}}, .phong_exp = 200, .smoothness = 10000},
//			.center = (cl_float3){{-1, -0.5f, -1}},
//			.radius = 1.5f};

//	objects[8] = (t_object){.type = TRIANGLE,
//			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = 0.9, .smoothness = 5000},
//			.vertices[0] = (cl_float3){{0, -2.5, 0}},
//			.vertices[1] = (cl_float3){{-2.5, 2, 0}},
//			.vertices[2] = (cl_float3){{0, 2, 2.5}},
//			.normal = (cl_float3){{0, 0, 1}}};

	return (objects);
}

static	t_object	*obj_scene(int *out_obj_nbr)
{
	const int	objects_nbr = 1;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

//	objects[0] = (t_object){.type = PLANE, // bottom
//			(t_material){.albedo = get_float3_color(COL_WHITE), .specular = 0, .smoothness = 0},
//			.center = (cl_float3){{0, -2.5, 0}},
//			.normal = (cl_float3){{0, 1, 0}}};

	objects[0] = (t_object){.type = SPHERE, // light
			(t_material){.albedo = get_float3_color(0), .specular = 0, .smoothness = 0,
					.emission_color = get_float3_color(COL_WHITE), .emission_power = 20},
			.center = (cl_float3){{20, 23, 0}},
			.radius = 6.f};

	return (objects);
}

static	t_object	*rt_get_objects(int *out_obj_nbr)
{

//	return (kolyan_scene(out_obj_nbr));
	return (cornell_box(out_obj_nbr));
//	return (pathtrace_objects(out_obj_nbr));
//	return (obj_scene(out_obj_nbr));
//	return (raytrace_objects(out_obj_nbr));
}

static t_light		*rt_get_lights(int *out_lights_nbr)
{
	const int	lights_nbr = 2;
	t_light		*lights;

	*out_lights_nbr = lights_nbr;
	lights = rt_safe_malloc(sizeof(t_light) * lights_nbr);
	lights[0] = (t_light){.color = get_float3_color(COL_WHITE), .type = AMBIENT, .intensity = 0.1f};
	lights[1] = (t_light){.pos = {{0, 0, -5}}, .color = get_float3_color(COL_WHITE), .type = POINT, .intensity = 0.3f};
//	lights[1] = (t_light){.dir = {{0, -1, 1}}, .color = get_float3_color(COL_WHITE), .type = DIRECTIONAL, .intensity = 0.8};
//	lights[2] = (t_light){.pos = {{1, 0.5, 2}}, .color = {COL_GREEN}, .type = POINT, .intensity = 0.9};
	return (lights);
}

t_scene		get_hardcoded_scene(void)
{
	t_scene		scene;

	scene.camera = (t_camera)
	{
//		.pos = (cl_float3){{0, 10, 40}}, //statuya pos/rot
//		.rotation = (cl_float3){{0, 180, 0}},
//		.pos = (cl_float3){{20, 6.6, -6.4}}, //pathtracing scene pos/rotation
//		.rotation = (cl_float3){{-10, -63.3, 0}},
		.pos = (cl_float3){{0.2, 1.2, -14.2}}, // cornell box pos/rotation
		.rotation = (cl_float3){{0, 0, 0}},
		.viewport_distance = 1,
		.viewport_width = WIN_RATIO < 1 ? D_I_MAZOHIN : 1,
		.viewport_height = WIN_RATIO > 1 ? D_E_KARMATSKIY : 1
	};
	scene.objects = rt_get_objects(&scene.obj_nbr);
	scene.lights = rt_get_lights(&scene.lights_nbr);
	return (scene);
}
