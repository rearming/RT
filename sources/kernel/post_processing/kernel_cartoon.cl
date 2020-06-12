
#include "opencl_defines.cl"
#include "rt_defines.h"
#include "rt_window_params.h"
#include "rt_colors.h"
#include "rt_shared_structs.h"
#include "opencl_structs.cl"
#include "prototypes.cl"

#include "color_utils.cl"
#include "math_utils.cl"
#include "utils.cl"
#include "post_processing_utils.cl"

float		sobel_get_weight_x(__global const int *img, int img_x, int img_y)
{
	const float		kernel_x[3][3] = {
			{-1, 0, +1},
			{-2, 0, +2},
			{-1, 0, +1}
	};

	float3	result = 0;

	int		k_y = 0;

	for (int y = img_y - 1; y <= img_y + 1; ++y)
	{
		int		k_x = 0;

		for (int x = img_x - 1; x <= img_x + 1; ++x)
		{
			float3	pixel_color;
			get_pixel(img, &pixel_color, x, y);
			result.x += pixel_color.x * kernel_x[k_y][k_x];
			result.y += pixel_color.y * kernel_x[k_y][k_x];
			result.z += pixel_color.z * kernel_x[k_y][k_x];
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

	for (int y = img_y - 1; y <= img_y + 1; ++y)
	{
		int		k_x = 0;

		for (int x = img_x - 1; x <= img_x + 1; ++x)
		{
			float3	pixel_color;
			get_pixel(img, &pixel_color, x, y);
			result.x += pixel_color.x * kernel_y[k_y][k_x];
			result.y += pixel_color.y * kernel_y[k_y][k_x];
			result.z += pixel_color.z * kernel_y[k_y][k_x];
			k_x++;
		}
		k_y++;
	}
	return fabs(result.x) + fabs(result.y) + fabs(result.z);
}

#define SOBEL_THRESHOLD 1
#define LINE_THICKNESS 3

__kernel void		kernel_cartoon(
	__global int *img_data,
	__global int *out_img_data)
{
	int		g_id = get_global_id(0);
	int3	img_point = get_img_point(g_id);
	int		pixel_color = img_data[g_id];

	float	x_sobel_value = sobel_get_weight_x(img_data, img_point.x, img_point.y);
	float	y_sobel_value = sobel_get_weight_y(img_data, img_point.x, img_point.y);
	float	weight = native_sqrt(x_sobel_value * x_sobel_value + y_sobel_value * y_sobel_value);

	if (weight < SOBEL_THRESHOLD)
	{
		out_img_data[g_id] = pixel_color;
		return;
	}
	const int	upper = (LINE_THICKNESS - 1) / 2;
	const int	lower = -upper;

	for (int y = lower; y < upper; ++y)
	{
		for (int x = lower; x < upper; ++x)
		{
			pixel_color = COL_LIGHT_BROWN;
			int2	pixel = (int2)(img_point.x + x, img_point.y + y);

			if (pixel_in_img(pixel.x, pixel.y))
				out_img_data[pixel.x + pixel.y * WIN_WIDTH] = pixel_color;
		}
	}
}