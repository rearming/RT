
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"

#include "math_utils.cl"
#include "utils.cl"

float3		sobel_get_pixel(__global __read_only const int *img, int x, int y)
{
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		t_color		color = {img[x + y * WIN_WIDTH]};
		return (float3)(color.rgb.r, color.rgb.g, color.rgb.b);
	}
	return 0;
}

float		sobel_get_weight_x(__global __read_only const int *img, int img_x, int img_y)
{
	const float		kernel_x[3][3] = {
			{-1, 0, +1},
			{-2, 0, +2},
			{-1, 0, +1}
	};

	float3	result = 0;

	int		k_y = 0;
#pragma unroll
	for (int y = img_y - 1; y <= img_y + 1; ++y)
	{
		int		k_x = 0;
#pragma unroll
		for (int x = img_x - 1; x <= img_x + 1; ++x)
		{
			result.x += sobel_get_pixel(img, x, y).x * kernel_x[k_y][k_x];
			result.y += sobel_get_pixel(img, x, y).y * kernel_x[k_y][k_x];
			result.z += sobel_get_pixel(img, x, y).z * kernel_x[k_y][k_x];
			k_x++;
		}
		k_y++;
	}
	return fabs(result.x) + fabs(result.y) + fabs(result.z);
}

float		sobel_get_weight_y(__global __read_only const int *img, int img_x, int img_y)
{
	const float		kernel_y[3][3] = {
			{+1, +2, +1},
			{0, 0, 0},
			{-1, -2, -1}
	};

	float3	result = 0;

	int		k_y = 0;
#pragma unroll
	for (int y = img_y - 1; y <= img_y + 1; ++y)
	{
		int		k_x = 0;
#pragma unroll
		for (int x = img_x - 1; x <= img_x + 1; ++x)
		{
			result.x += sobel_get_pixel(img, x, y).x * kernel_y[k_y][k_x];
			result.y += sobel_get_pixel(img, x, y).y * kernel_y[k_y][k_x];
			result.z += sobel_get_pixel(img, x, y).z * kernel_y[k_y][k_x];
			k_x++;
		}
		k_y++;
	}
	return fabs(result.x) + fabs(result.y) + fabs(result.z);
}

#define SOBEL_THRESHOLD 100

__kernel void		rays_gen(
	__global __read_only t_scene *scene,
	__global __read_only int *img_data,
	__global __write_only t_ray *rays)
{
	int3		img_point = (int3)(get_global_id(0), get_global_id(1), 0);
	int			g_id = img_point.x + img_point.y * WIN_WIDTH;

//	rays[RAYS_CHUNK_SIZE * g_id + 4] = get_ray(convert_float3(img_point), &scene->camera);
	float		x_sobel_value = sobel_get_weight_x(img_data, img_point.x, img_point.y);
	float		y_sobel_value = sobel_get_weight_y(img_data, img_point.x, img_point.y);
	float		weight = native_sqrt(x_sobel_value * x_sobel_value + y_sobel_value * y_sobel_value);

	int		i = 0;

#pragma unroll
	for (int y = -1; y < 2; ++y)
	{
#pragma unroll
		for (int x = -1; x < 2; ++x)
		{
			float3	origin = (float3)(img_point.x + x, img_point.y + y, 0);

			rays[i + g_id * RAYS_CHUNK_SIZE] =
					weight > SOBEL_THRESHOLD
					? get_ray(origin, &scene->camera)
					: (t_ray){0, 0, -1};
			i++;
		}
	}
	rays[RAYS_CHUNK_SIZE * g_id + 4] = get_ray(convert_float3(img_point), &scene->camera);
}
