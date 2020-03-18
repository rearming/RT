
#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
#include "prototypes.cl"

#include "color_utils.cl"
#include "utils.cl"

bool			get_pixel(__global const int *img_data, float3 *out_pixel, int x, int y)
{
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		*out_pixel = get_float3_color(img_data[x + y * WIN_WIDTH]);
		return true;
	}
	return false;
}

#define GAUSS_TWO_PI 6.28319f
#define GAUSS_E 2.71828f
#define SPREAD 5.0f

float			calc_gauss(int x)
{
	float sigma_sqr = SPREAD * SPREAD;

	return (1 / sqrt(GAUSS_TWO_PI * sigma_sqr)) * pow(GAUSS_E, -(x * x) / (2 * sigma_sqr));
//	return 1.f;
}

float3			process_pixel_horizontal(
		__global const int *img_data,
		int2 img_point,
		int	blur_coeff,
		float *out_kernel_sum)
{
	const int	upper = (blur_coeff - 1) / 2;
	const int	lower = -upper;

	float		kernel_sum = 0.0f;
	float3		result = 0;

	for (int x = lower; x <= upper; x++)
	{
		float3	pixel_color;
		float	gauss = calc_gauss(x); //это потом можно будет сохранить в матрицу

		if (get_pixel(img_data, &pixel_color, img_point.x + x, img_point.y))
		{
			result += pixel_color * gauss;
			kernel_sum += gauss;
		}
	}
	*out_kernel_sum += kernel_sum;
	return (result);
}

float3			process_pixel_vertical(
		__global const int *img_data,
		int2 img_point,
		int blur_coeff,
		float *out_kernel_sum)
{
	const int	upper = (blur_coeff - 1) / 2;
	const int	lower = -upper;

	float		kernel_sum = 0.0f;
	float3		result = 0;

	for (int y = lower; y <= upper; y++)
	{
		float3	pixel_color;
		float	gauss = calc_gauss(y); //это потом можно будет сохранить в матрицу

		if (get_pixel(img_data, &pixel_color, img_point.x, img_point.y + y))
		{
			result += pixel_color * gauss;
			kernel_sum += gauss;
		}
	}
	*out_kernel_sum += kernel_sum;
	return (result);
}

__kernel void	kernel_gaussian_blur(
		__global const int *img_data,
		__global int *out_img_data)
{
	int		g_id = get_global_id(0);
	int3	img_point = get_img_point(g_id);

	float	kernel_sum = 0;
	float3	result_color = 0;

	result_color += process_pixel_horizontal(img_data, img_point.xy, 5, &kernel_sum);
	result_color += process_pixel_vertical(img_data, img_point.xy, 5, &kernel_sum);
	result_color /= kernel_sum;

	out_img_data[g_id] = get_int_color(result_color);
}
