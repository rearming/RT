#include "rt.h"
#include "rt_math_utils.h"
#include "rt_debug.h"

static	t_object	*kolyan_scene(int *out_obj_nbr)
{
	const int	objects_nbr = 8;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);
	objects[0] = (t_object){.type = PLANE,
			(t_material){.diffuse = get_float3_color(COL_LIGHT_GREEN), .specular = {{0.9f, 0.9f, 0.9f}}, .smoothness = MAX_SMOOTHNESS},
			.center = {{25, 0, 0}},
			.normal = {{-0.6, 0, 0}}};
	objects[1] = (t_object){.type = PLANE,
			(t_material){.diffuse = get_float3_color(COL_LIGHT_GREY), .specular = {{0.9f, 0.9f, 0.9f}}, .smoothness = MAX_SMOOTHNESS},
			.center = {{-25, 0, 0}},
			.normal = {{0.6, 0, 0}}};
	objects[2] = (t_object){.type = PLANE,
			(t_material){.diffuse = get_float3_color(COL_DARK_PURPLE), .specular = {{0.9f, 0.9f, 0.9f}}, .smoothness = MAX_SMOOTHNESS},
			.center = {{0, 25, 0}},
			.normal = {{0, -0.6, 0}}};
	objects[3] = (t_object){.type = PLANE,
			(t_material){.diffuse = get_float3_color(COL_LIGHT_RED), .specular = {{0.9f, 0.9f, 0.9f}}, .smoothness = MAX_SMOOTHNESS},
			.center = {{0, -25, 0}},
			.normal = {{0, 0.6, 0}}};
	objects[4] = (t_object){.type = PLANE,
			(t_material){.diffuse = get_float3_color(COL_LIGHT_BLUE), .specular = {{0.9f, 0.9f, 0.9f}}, .smoothness = MAX_SMOOTHNESS},
			.center = {{0, 0, 25}},
			.normal = {{0, 0, -0.6}}};
	objects[5] = (t_object){.type = PLANE,
			(t_material){.diffuse = get_float3_color(COL_DARK_GREEN), .specular = {{0.9f, 0.9f, 0.9f}}, .smoothness = MAX_SMOOTHNESS},
			.center = {{0, 0, -25}},
			.normal = {{0, 0, 1}}};
	objects[6] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{1.f, 1.f, 1.f}}, .smoothness = 1000},
			.center = {{0, 0, 0}},
			.radius = 2.5};
	objects[7] = (t_object){.type = SPHERE,
			(t_material){.emission_color = get_float3_color(COL_WHITE), .emission_power = 200},
			.center = {{0, 10, 0}},
			.radius = 2.5};
	return (objects);

}

static	t_object	*pathtrace_scene(int *out_obj_nbr)
{
	const int	objects_nbr = 12;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

	objects[0] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(COL_DARK_RED), .specular = {{0.7f, 0.7f, 0.7f}}, .smoothness = 100},
			.center = {{0, 2.6, 0}},
			.radius = 2.5};
	objects[1] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(COL_LIGHT_GREEN), .specular = {{0.f, 0.f, 0.f}}},
			.center = {{4, 1, 0}},
			.radius = 1};
	objects[2] = (t_object){.type = SPHERE, /// golden sphere
			(t_material){.diffuse = get_float3_color(COL_GOLD), .specular = {{1.0f, 1.0f, 1.0f}}, .smoothness = 2000.f},
			.center = {{5, 1, 3}},
			.radius = 1};
	objects[3] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(COL_LIGHT_PURPLE), .specular = {{1.0f, 1.0f, 1.0f}}, .smoothness = 20},
			.center = {{10, 2.4, 6}},
			.radius = 2.2};
	objects[4] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(0), .specular = {{0.f, 0.f, 0.f}},
				.emission_color = get_float3_color(COL_LIGHT_BLUE), .emission_power = 10},
			.center = {{-1, 0.5, 5}},
			.radius = 1};
	objects[5] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(0), .specular = {{0.f, 0.f, 0.f}},
				.emission_color = get_float3_color(COL_WHITE), .emission_power = 10},
			.center = {{7, 0, 2}},
			.radius = 0.8};
	objects[6] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(0), .specular = {{1.0f, 1.0f, 1.0f}}, .smoothness = MAX_SMOOTHNESS},
			.center = {{4, 2, -5}},
			.radius = 2};
	objects[7] = (t_object){.type = PLANE,
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0.f, 0.f, 0.f}}, .smoothness = 0},
			.center = {{0, 0, 0}},
			.normal = {{0, 1, 0}}};
	objects[9] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(0), .specular = {{0.f, 0.f, 0.f}},
					.emission_color = get_float3_color(COL_WHITE), .emission_power = 10},
			.center = {{700, 300, 700}},
			.radius = 100};

	objects[10] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{1.f, 1.f, 1.f}},
					.smoothness = MAX_SMOOTHNESS, .refraction = 1.15, .transmittance = 1},
			.center = {{15, 2.2, -6.2}},
			.radius = 2};
	objects[11] = (t_object){.type = SPHERE,
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{1.f, 1.f, 1.f}},
					.smoothness = MAX_SMOOTHNESS - 1, .refraction = 1.15, .transmittance = 1},
			.center = {{15, 2.6, -1.2}},
			.radius = 2};

	return (objects);
}

static	t_object	*cornell_box(int *out_obj_nbr)
{
	const int	objects_nbr = 9;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

	objects[0] = (t_object){.type = PLANE, // bottom
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0, 0, 0}}, .phong_exp = 0, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{0, -2.5, 0}},
			.normal = {{0, 1, 0}}};
	objects[1] = (t_object){.type = PLANE, // right
			(t_material){.diffuse = get_float3_color(COL_GREEN), .specular = {{0, 0, 0}}, .phong_exp = 50, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{2.5, 0, 0}},
			.normal = {{1, 0, 0}}};
	objects[2] = (t_object){.type = PLANE, // left
			(t_material){.diffuse = get_float3_color(COL_RED), .specular = {{0, 0, 0}}, .phong_exp = 0, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{-2.5, 0, 0}},
			.normal = {{1, 0, 0}}};
	objects[3] = (t_object){.type = PLANE, // far
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0, 0, 0}}, .phong_exp = 40, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{0, 0, 2.5}},
			.normal = {{0, 0, 1}}};
	objects[4] = (t_object){.type = PLANE, // celling
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0, 0, 0}}, .phong_exp = 0, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{0, 2.5, 0}},
			.normal = {{0, 1, 0}}};
	objects[5] = (t_object){.type = PLANE, // back
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0, 0, 0}}, .phong_exp = 0, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{0, 0, -15}},
			.normal = {{0, 0, 1}}};

	objects[6] = (t_object){.type = SPHERE, // light
			(t_material){.diffuse = get_float3_color(0), .specular = {{0, 0, 0}}, .phong_exp = 0, .smoothness = 0,
				.emission_color = get_float3_color(COL_WHITE), .emission_power = 1, .texture_number = NOT_SET},
			.center = {{0, 2.5, 0}},
			.radius = 1.5f};

/*	objects[7] = (t_object){.type = SPHERE, // specular sphere
			(t_material){.specular = {{1, 1, 1}}, .phong_exp = 0, .smoothness = 10000},
			.center = {{1, -1.5f, 0}},
			.radius = 1.f};*/

//	objects[7] = (t_object){.type = SPHERE, // texture sphere
//			(t_material){.diffuse = get_float3_color(COL_WHITE), .phong_exp = 0, .smoothness = 10000, .texture_number = 1},
//			.center = {{1, -1.5f, 0}},
//			.radius = 2.f};

	objects[7] = (t_object){.type = AABB, // texture sphere
			(t_material){.diffuse = get_float3_color(COL_GREEN), .texture_number = NOT_SET},
			.vmin = (cl_float3){{0, 0, -2}},
			.vmax = (cl_float3){{1, 1, 1}}};

	objects[8] = (t_object){.type = SPHERE, // specular sphere
			(t_material){.specular = get_float3_color(COL_LIGHT_GREEN), .transmittance = 0, .refraction = 0,
				.phong_exp = 200, .smoothness = 1000, .texture_number = NOT_SET},
			.center = {{-1, -0.5f, -2.5}},
			.radius = 1.f};

//	objects[8] = (t_object){.type = TRIANGLE,
//			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0.9f, 0.9f, 0.9f}}, .smoothness = 5000},
//			.vertices[0] = {{0, -2.5, 0}},
//			.vertices[1] = {{-2.5, 2, 0}},
//			.vertices[2] = {{0, 2, 2.5}},
//			.normal = {{0, 0, 1}}};

	return (objects);
}

static	t_object	*obj_scene(int *out_obj_nbr)
{
	const int	objects_nbr = 1;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

//	objects[0] = (t_object){.type = PLANE, // bottom
//			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = 0, .smoothness = 0},
//			.center = {{0, -2.5, 0}},
//			.normal = {{0, 1, 0}}};

	objects[0] = (t_object){.type = SPHERE, // light
			(t_material){.diffuse = get_float3_color(0), .specular = {{0.f, 0.f, 0.f}}, .smoothness = 0,
					.emission_color = get_float3_color(COL_WHITE), .emission_power = 20},
			.center = {{20, 23, 0}},
			.radius = 6.f};
	return (objects);
}

#ifdef __APPLE__
# define scene_random arc4random
#else
# define scene_random rand
#endif

static	t_object	*many_spheres_test(int *out_obj_nbr)
{
	const int	objects_nbr = 100;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);

	objects[0] = (t_object){.type = PLANE, // bottom
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = (cl_float3){{0.f, 0.f, 0.f}}, .smoothness = 0},
			.center = {{0, -1, 0}},
			.normal = {{0, 1, 0}}};

	float	sqrt_obj_nbr = sqrtf((float)objects_nbr);
	cl_float2	sphere_pos = (cl_float2){{-sqrt_obj_nbr, -sqrt_obj_nbr}};

	for (int i = 1; i < *out_obj_nbr; ++i)
	{
		bool		metal = scene_random() % 2 == 0 ? true : false;
		cl_float3	color = (cl_float3){{drand48(), drand48(), drand48()}};
		cl_float3	diffuse = metal ? (cl_float3){{0, 0, 0}} : color;
		cl_float3	specular = metal ? color : (cl_float3){{0.0, 0.0, 0.0}};
		cl_float	smoothness = scene_random() % 30000;
		bool		is_light = scene_random() % 6 == 0 ? true : false;

		cl_float	radius = ft_clampf((float)drand48() * 3.f, 1, 3);
		cl_float3	center = (cl_float3){{sphere_pos.x, radius, sphere_pos.y}};
		objects[i] = (t_object){.type = SPHERE, .material = {
				.diffuse = diffuse, .specular = specular, .smoothness = smoothness,
				.emission_color = is_light ? color : (cl_float3){{0, 0, 0}}, .emission_power = is_light ? scene_random() % 20 : 0},
						  .center = center, .radius = radius};
		sphere_pos.x += radius + drand48();
		if (i % (int)sqrt_obj_nbr == 0)
			sphere_pos.x = -sqrt_obj_nbr;
		sphere_pos.x += radius + drand48() * 2;
		sphere_pos.y += radius + drand48() * 2;
	}
//	for (int j = 1; j < *out_obj_nbr; ++j)
//		rt_print_sphere(&objects[j]);
	return (objects);
}

static	t_object	*texture_scene(int *out_obj_nbr)
{
	const int	objects_nbr = 5;
	t_object	*objects;

	*out_obj_nbr = objects_nbr;
	objects = rt_safe_malloc(sizeof(t_object) * objects_nbr);
	objects[0] = (t_object){.type = NOT_SET, // far
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0, 0, 0}}, .phong_exp = 40, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{0, 0, 2.5}},
			.normal = {{0, 0, 1}}};
	objects[1] = (t_object){.type = NOT_SET, // back
			(t_material){.diffuse = get_float3_color(COL_WHITE), .specular = {{0, 0, 0}}, .phong_exp = 0, .smoothness = 0, .texture_number = NOT_SET},
			.center = {{0, 0, -15}},
			.normal = {{0, 0, 1}}};
	objects[2] = (t_object){.type = SPHERE, // light
			(t_material){.diffuse = get_float3_color(0), .specular = {{0, 0, 0}}, .phong_exp = 0, .smoothness = 0,
					.emission_color = get_float3_color(COL_WHITE), .emission_power = 1, .texture_number = NOT_SET},
			.center = {{0, 2.5, 0}},
			.radius = 1.5f};
	objects[3] = (t_object){.type = SPHERE, // texture sphere
			(t_material){.diffuse = get_float3_color(COL_WHITE), .phong_exp = 0, .smoothness = 10000, .texture_number = 1},
			.center = {{1, -1.5f, 0}},
			.radius = 2.f};
	objects[4] = (t_object){.type = SPHERE, // texture sphere
			(t_material){.diffuse = get_float3_color(COL_WHITE), .phong_exp = 0, .smoothness = 1000, .texture_number = 0},
			.center = {{-1, -0.5f, -2.5}},
			.radius = 1.f};
	return (objects);
}

static t_object		*rt_get_objects(int *out_obj_nbr)
{
//	return (cornell_box(out_obj_nbr));
//	return (kolyan_scene(out_obj_nbr));
//	return (many_spheres_test(out_obj_nbr));
//	return (pathtrace_scene(out_obj_nbr));
	return (obj_scene(out_obj_nbr));
//	return (texture_scene(out_obj_nbr));
	RT_UNUSED(cornell_box(out_obj_nbr));
	RT_UNUSED(kolyan_scene(out_obj_nbr));
	RT_UNUSED(many_spheres_test(out_obj_nbr));
	RT_UNUSED(pathtrace_scene(out_obj_nbr));
	RT_UNUSED(obj_scene(out_obj_nbr));
	RT_UNUSED(texture_scene(out_obj_nbr));
}

static t_light		*rt_get_lights(int *out_lights_nbr)
{
	const int	lights_nbr = 2;
	t_light		*lights;

	*out_lights_nbr = lights_nbr;
	lights = rt_safe_malloc(sizeof(t_light) * lights_nbr);
	lights[0] = (t_light){.color = get_float3_color(COL_WHITE), .type = AMBIENT, .intensity = 0.2f};
//	lights[1] = (t_light){.pos = {{0, 10, -5}}, ///для pathtrace scene
//		.color = get_float3_color(COL_WHITE), .type = POINT, .intensity = 0.5f};
	lights[1] = (t_light){.pos = {{0, 0, -5}}, /// для cornell box
					   .color = get_float3_color(COL_WHITE), .type = POINT, .intensity = 0.5f};
//	lights[1] = (t_light){.dir = {{0, -1, 10}}, .color = get_float3_color(COL_WHITE), .type = DIRECTIONAL, .intensity = 0.5};
//	lights[2] = (t_light){.pos = {{1, 0.5, 2}}, .color = {COL_GREEN}, .type = POINT, .intensity = 0.9};
	return (lights);
}

static void 	add_textures(void)
{
	int i;

	i = 0;
	char *textures[] = {
			"sphere_eye.jpg",
			"skybox_cave.jpg"};

	g_textures.texture_info_size = sizeof(textures) / sizeof(char*);
	g_textures.textures_names = NULL;
	while (i < (int)g_textures.texture_info_size)
	{
		ft_add_texture_name_back(&g_textures.textures_names, textures[i]);
		i++;
	}
}

void			print_textures(void)
{
	t_texture_name *tmp;
	tmp = g_textures.textures_names;
	while (tmp)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}

t_scene		get_hardcoded_scene(void)
{
	t_scene		scene;

	scene.camera = (t_camera)
	{
		.pos = {{0, 2, 10}}, //statuya pos/rot
		.rotation = {{0, 180, 0}},
//		.pos = {{20, 6.6, -6.4}}, //pathtracing scene pos/rotation
//		.rotation = {{-10, -63.3, 0}},
//		.pos = {{0.2, 1.2, -14.2}}, // cornell box pos/rotation
//		.rotation = {{0, 0, 0}}, // kd-test pos
//		.pos = {{0, 28, 500}}, //traverse pos
//		.rotation = {{0, 180, 0}},
		.viewport_distance = 1,
		.viewport_width = WIN_RATIO < 1 ? D_I_MAZOHIN : 1,
		.viewport_height = WIN_RATIO > 1 ? D_E_KARMATSKIY : 1
	};
	scene.objects = rt_get_objects(&scene.obj_nbr);
	scene.lights = rt_get_lights(&scene.lights_nbr);
	add_textures();
	//print_textures();
	return (scene);
}
