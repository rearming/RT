#include "rt.h"
#include "rt_debug.h"
#include "rt_math_utils.h"
#include "rt_kd_tree.h"

static cl_float3	canvas_to_viewport(int x, int y)
{
	return (cl_float3)
	{
		.x = (float)x * (WIN_RATIO < 1 ? D_I_MAZOHIN : 1) / WIN_WIDTH,
		.y = (float)y * (WIN_RATIO > 1 ? D_E_KARMATSKIY : 1) / WIN_HEIGHT,
		.z = 1
	};
}

static t_ray get_ray(int x, int y, float test_kek_y, float test_kek_z)
{
	t_ray	ray;

	x -= WIN_WIDTH / 2;
	y -= WIN_HEIGHT / 2;
	y *= -1;
	ray.dir = vec_normalize(canvas_to_viewport(x, y));
	rt_rotate_point(&ray.dir, (cl_float3){{0, M_PI, 0}});
	ray.origin = (cl_float3){{0, test_kek_y, test_kek_z}};
	return ray;
}

void test_kd_traverse(t_kd_tree *tree, t_ray ray, int *indices)
{
	bool	res_traverse = kd_tree_traverse(tree, ray, indices);

//	printf("traversed with:\n");
//	rt_print_clfloat3(ray.origin, "ray.origin");
//	rt_print_clfloat3(ray.dir, "ray.dir");
//	printf("%s\n\n", res_traverse ? "SUCCESS" : "FAIL");
}

void	kd_run_traverse_tests(t_kd_tree *tree)
{
	t_ray	ray;
	int		*indices = rt_safe_malloc(sizeof(int) * 7000);

	for (int i = 0; i < 7000; ++i)
		indices[i] = NOT_SET;

	for (int k = 1; k < 20; ++k)
	{
		for (int y = 0; y < WIN_HEIGHT; ++y)
		{
			for (int x = 0; x < WIN_WIDTH; ++x)
			{
				ray = get_ray(x, y, (float)k * 1.5f, (float)k * 50.0f);
				test_kd_traverse(tree, ray, indices);
			}
		}
		int		indices_found = 0;
		for (int j = 0; j < 7000; ++j)
		{
			if (indices[j] != NOT_SET)
				indices_found++;
		}
		printf("indices found: [%i], with y_kek = [%.3f], z_kek = [%.3f]\n", indices_found, k * 1.5, (float)k * 50);
	}

//	ray = (t_ray){.dir = (cl_float3){{0.001, 0.001, 0.7}}, .origin = (cl_float3){{0, 0, -10}}};
//	test_kd_traverse(tree, ray);
//
//	ray = (t_ray){.dir = (cl_float3){{0.7, 0.001, 0.001}}, .origin = (cl_float3){{0, 0, -10}}};
//	test_kd_traverse(tree, ray);
//
//	ray = (t_ray){.dir = (cl_float3){{0.3, 0.2, 0.3}}, .origin = (cl_float3){{0, 0, -10}}};
//	test_kd_traverse(tree, ray);
//
//	ray = (t_ray){.dir = (cl_float3){{0.001, -0.03, 0.5}}, .origin = (cl_float3){{0, 0, -10}}};
//	test_kd_traverse(tree, ray);
//
//	ray = (t_ray){.dir = (cl_float3){{0.0001, 0.15, 0.9}}, .origin = (cl_float3){{0, 0, -10}}};
//	test_kd_traverse(tree, ray);
//
//	ray = (t_ray){.dir = (cl_float3){{0.001, 0.001, 0.7}}, .origin = (cl_float3){{0, 0, -10}}};
//	test_kd_traverse(tree, ray);
}