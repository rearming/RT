
#include "kernel_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "kernel_structs.cl"
#include "prototypes.cl"

#include "math_utils.cl"
#include "utils.cl"

float3		sobel_get_pixel(__global const int *img, int x, int y)
{
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		t_color		color = {img[x + y * WIN_WIDTH]};
		return (float3)(color.rgb.r, color.rgb.g, color.rgb.b);
	}
	return 0;
}

float		sobel_get_weight_x(__global const int *img, int img_x, int img_y)
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

float		sobel_get_weight_y(__global const int *img, int img_x, int img_y)
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

__kernel void		kernel_anti_aliasing_rays_generation(
	__global const t_camera *camera,
	__global int *img_data,
	__global t_ray *out_rays_buffer,
	__global int *out_pixel_indices,
	__global int *out_rays_buffer_len)
{
	int		g_id = get_global_id(0);
	int3	img_point = get_img_point(g_id);

	float	x_sobel_value = sobel_get_weight_x(img_data, img_point.x, img_point.y);
	float	y_sobel_value = sobel_get_weight_y(img_data, img_point.x, img_point.y);
	float	weight = native_sqrt(x_sobel_value * x_sobel_value + y_sobel_value * y_sobel_value);

	int		i = 0;

	t_ray	rays[9];

	rays[0] = (t_ray){(float3)(1, 2, 3), (float3)(4, 5, 6), (float3)(7, 8, 9)};
	rays[1] = (t_ray){(float3)(11, 12, 13), (float3)(14, 15, 16), (float3)(17, 18, 19)};
	rays[2] = (t_ray){(float3)(21, 22, 23), (float3)(24, 25, 26), (float3)(27, 28, 29)};
	rays[3] = (t_ray){(float3)(31, 32, 33), (float3)(34, 35, 36), (float3)(37, 38, 39)};
	rays[4] = (t_ray){(float3)(41, 42, 43), (float3)(44, 45, 46), (float3)(47, 48, 49)};
	rays[5] = (t_ray){(float3)(51, 52, 53), (float3)(54, 55, 56), (float3)(57, 58, 59)};
	rays[6] = (t_ray){(float3)(61, 62, 63), (float3)(64, 65, 66), (float3)(67, 68, 69)};
	rays[7] = (t_ray){(float3)(71, 72, 73), (float3)(74, 75, 76), (float3)(77, 78, 79)};
	rays[8] = (t_ray){(float3)(81, 82, 83), (float3)(84, 85, 86), (float3)(87, 88, 89)};

	if (weight < SOBEL_THRESHOLD)
	{
		uint cached_buffer_len = atomic_inc(out_rays_buffer_len);
//		out_rays_buffer[cached_buffer_len] = get_ray(convert_float3(img_point), camera);
		out_rays_buffer[cached_buffer_len] = (t_ray){(float3)(-69), (float3)(-69), (float3)(-69)};
		return;
	}
	for (int y = -1; y < 2; ++y)
	{
		for (int x = -1; x < 2; ++x)
		{
			float3	origin = (float3)(img_point.x + x * 0.5f, img_point.y + y * 0.5f, 0.0f);

			uint cached_buffer_len = atomic_inc(out_rays_buffer_len);
//			printf("cached buffer len: [%u]\n", cached_buffer_len);
//			out_rays_buffer[cached_buffer_len] = (t_ray){(float3)(0), (float3)(0), (float3)(0)};
//			t_ray suka_ray = get_ray(convert_float3(img_point), *camera);
//			out_rays_buffer[cached_buffer_len] = get_ray(origin, camera);
//			out_rays_buffer[cached_buffer_len] = (t_ray){(float3)(1, 4, 5), (float3)(2), (float3)(3)};
			out_rays_buffer[cached_buffer_len] = rays[i];
//			out_rays_buffer[cached_buffer_len] = (t_ray){(float3)(1), (float3)(2), (float3)(3)};
//			out_rays_buffer[cached_buffer_len] = suka_ray;
//			out_rays_buffer[cached_buffer_len] = (t_ray){
//			out_rays_buffer[cached_buffer_len] = (t_ray){(float3)(0), (float3)(0), (float3)(0)};
//				(float3)(suka_ray.origin.x, suka_ray.origin.y, suka_ray.origin.z),
//				(float3)(suka_ray.dir.x, suka_ray.dir.y, suka_ray.dir.z),
//				(float3)(suka_ray.energy.x, suka_ray.energy.y, suka_ray.energy.z)
//			};
//			printf("origin %f %f %f\tdir %f %f %f\tenergy %f %f %f\n",
//					suka_ray.origin.x, suka_ray.origin.y, suka_ray.origin.z,
//					suka_ray.dir.x, suka_ray.dir.y, suka_ray.dir.z,
//					suka_ray.energy.x, suka_ray.energy.y, suka_ray.energy.z);
//			printf("origin %f %f %f\tdir %f %f %f\tenergy %f %f %f\n",
//					out_rays_buffer[cached_buffer_len].origin.x, out_rays_buffer[cached_buffer_len].origin.y, out_rays_buffer[cached_buffer_len].origin.z,
//					out_rays_buffer[cached_buffer_len].dir.x, out_rays_buffer[cached_buffer_len].dir.y, out_rays_buffer[cached_buffer_len].dir.z,
//					out_rays_buffer[cached_buffer_len].energy.x, out_rays_buffer[cached_buffer_len].energy.y, out_rays_buffer[cached_buffer_len].energy.z);
//			(t_ray){(float3)(124.f, 345234.f, -4.424), (float3)(12.1134f, -34.4533f, -422.424), (float3)(1.f)};
			out_pixel_indices[cached_buffer_len] = g_id;
			i++;
		}
	}
}
