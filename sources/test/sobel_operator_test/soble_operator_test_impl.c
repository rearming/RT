#include "sobel_operator_tests.h"
#include "test_header.h"

static inline cl_float3 sobel_get_pixel(t_sobel_img *img, int x, int y)
{
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		t_color		color = {img->data[x + y * img->width]};
		return (cl_float3){{color.rgb.r, color.rgb.g, color.rgb.b}};
	}
	return (cl_float3){{0, 0, 0}};
}

inline float sobel_process_pixel(t_sobel_img *img, int img_x, int img_y, int axis)
{
	cl_float3	result = (cl_float3){{0, 0, 0}};

	int		k_y = 0;

	for (int y = img_y - 1; y <= img_y + 1; ++y)
	{
		int		k_x = 0;
		for (int x = img_x - 1; x <= img_x + 1; ++x)
		{
			if (axis == X_AXIS)
			{
				result.x += sobel_get_pixel(img, x, y).x * kernel_x[k_y][k_x];
				result.y += sobel_get_pixel(img, x, y).y * kernel_x[k_y][k_x];
				result.z += sobel_get_pixel(img, x, y).z * kernel_x[k_y][k_x];

			}
			else
			{
				result.x += sobel_get_pixel(img, x, y).x * kernel_y[k_y][k_x];
				result.y += sobel_get_pixel(img, x, y).y * kernel_y[k_y][k_x];
				result.z += sobel_get_pixel(img, x, y).z * kernel_y[k_y][k_x];
			}
			k_x++;
		}
		k_y++;
	}
	return fabsf(result.x) + fabsf(result.y) + fabsf(result.z);
}

#define SOBEL_THRESHOLD 100

inline int get_sobel_color(float weigth)
{
	t_color		color;

	color.rgb.a = 0xFF;
	if (weigth > SOBEL_THRESHOLD)
	{
		color.rgb.r = 0xFF;
		color.rgb.g = 0xFF;
		color.rgb.b = 0xFF;
	}
	else
	{
		color.rgb.r = 0x0;
		color.rgb.g = 0x0;
		color.rgb.b = 0x0;
	}
	return color.value;
}

void		process_img_sobel(t_sobel_img *img)
{
	int		*new_img = rt_safe_malloc(img->width * img->height * sizeof(int));

	float max_weight = 0;

	for (int y = 0; y < img->height; ++y)
	{
		for (int x = 0; x < img->width; ++x)
		{
			float		x_sobel_value = sobel_process_pixel(img, x, y, X_AXIS);
			float		y_sobel_value = sobel_process_pixel(img, x, y, Y_AXIS);
			float		weight = 0;

			weight = sqrtf(x_sobel_value * x_sobel_value + y_sobel_value * y_sobel_value);
			max_weight = fmaxf(weight, max_weight);
			new_img[x + y * img->width] = get_sobel_color(weight);
		}
	}
	for (int i = 0; i < img->width * img->height; ++i)
	{
		img->data[i] = new_img[i];
	}
	free(new_img);
}
