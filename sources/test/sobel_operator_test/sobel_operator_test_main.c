#include "test_header.h"
#include <rt_math_utils.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct	s_sobel_img
{
	int			*data;
	int			width;
	int			height;
	int			num_channels;
}				t_sobel_img;

#define X_AXIS 0
#define Y_AXIS 1

const float		kernel_x[3][3] = {
		{-1, 0, +1},
		{-2, 0, +2},
		{-1, 0, +1}
};

const float		kernel_y[3][3] = {
		{+1, +2, +1},
		{0, 0, 0},
		{-1, -2, -1}
};

void		render_sobel_corners(void *ptr)
{
	t_sobel_img	*img = ptr;

	for (int y = 0; y < img->height; ++y)
	{
		for (int x = 0; x < img->width; ++x)
		{
			g_img_data[x + y * WIN_WIDTH] = img->data[x + y * img->width];
		}
	}
}

static inline cl_float3 sobel_get_pixel(t_sobel_img *img, int x, int y)
{
	if (x > 0 && y > 0 && x < img->width && y < img->height)
	{
		t_color		color = {img->data[x + y * img->width]};
		return (cl_float3){{color.rgb.r, color.rgb.g, color.rgb.b}};
	}
	return (cl_float3){{0, 0, 0}};
}

static inline float
sobel_process_pixel(t_sobel_img *img, int x, int y, int axis)
{
	float		result = 0;

	int		k_x = 0;

	for (int i = x - 1; i <= x + 1; ++i)
	{
		int		k_y = 0;
		for (int j = y - 1; j <= y + 1; ++j)
		{
			if (axis == X_AXIS)
			{
				result += sobel_get_pixel(img, i, j).x * kernel_x[k_y][k_x];
				result += sobel_get_pixel(img, i, j).y * kernel_x[k_y][k_x];
				result += sobel_get_pixel(img, i, j).z * kernel_x[k_y][k_x];

			}
			else
			{
				result += sobel_get_pixel(img, i, j).x * kernel_y[k_y][k_x];
				result += sobel_get_pixel(img, i, j).y * kernel_y[k_y][k_x];
				result += sobel_get_pixel(img, i, j).z * kernel_y[k_y][k_x];
			}
			k_y++;
		}
		k_x++;
	}
	return result;
}

static inline float	mapf(float value, float v_min, float v_max, float res_min, float res_max)
{
	//Y = (X-A)/(B-A) * (D-C) + C
	return (value - v_min) / (v_max - v_min) * (res_max - res_min) + res_min;
}

static inline int get_sobel_color(float weigth)
{
	t_color		color;

	color.rgb.a = 0xFF;
//	color.rgb.r = (int)mapf(weigth, 0.f, 2550.f, 0.f, 254.f);
//	color.rgb.g = (int)mapf(weigth, 0.f, 2550.f, 0.f, 254.f);
//	color.rgb.b = (int)mapf(weigth, 0.f, 2550.f, 0.f, 254.f);
	color.rgb.r = weigth / 9;
	color.rgb.g = weigth / 9;
	color.rgb.b = weigth / 9;
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
	printf("max weight: [%f]\n", max_weight);
}

t_sdl		g_sdl;
t_opencl	g_opencl;
int			*g_img_data;

void 	test_sobel_operator(const int field[3][3])
{
	t_sobel_img		test_img;

	test_img.width = 3;
	test_img.height = 3;
	test_img.data = malloc(sizeof(int) * 9);
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			test_img.data[x + y * 3] = field[y][x];
		}
	}

	float		x_sobel_value = sobel_process_pixel(&test_img, 1, 1, X_AXIS);
	float		y_sobel_value = sobel_process_pixel(&test_img, 1, 1, Y_AXIS);
	float		weight = 0;

	weight = sqrtf(x_sobel_value * x_sobel_value + y_sobel_value * y_sobel_value);
	printf("weight: [%f], x_sobel_value: [%f], y_sobel_value: [%f]\n", weight, x_sobel_value, y_sobel_value);
	t_color color;
	color.value = get_sobel_color(weight);
	printf("color.value: [0x%X], r: [%i], g: [%i], b: [%i]\n", color.value, color.rgb.r, color.rgb.g, color.rgb.b);
}

void 	prepare_test_field(int color_left, int color_right, int out_field[3][3])
{
	out_field[0][0] = color_left;
	out_field[1][0] = color_left;
	out_field[2][0] = color_left;
	out_field[0][1] = color_left;
	out_field[1][1] = color_left;
	out_field[2][1] = color_left;
	out_field[0][2] = color_right;
	out_field[1][2] = color_right;
	out_field[2][2] = color_right;
}

int		main(int argc, char **argv)
{
	int field[3][3];

	prepare_test_field(0xFF0000, 0x0000FF, field);
	test_sobel_operator(field);

	prepare_test_field(0x00FF00, 0x0000FF, field);
	test_sobel_operator(field);

	prepare_test_field(0x737300, 0x750075, field);
	test_sobel_operator(field);
//	const int	field_green_blue[3][3] = {
//			{0x00FF00, 0x00FF00, 0x0000FF},
//			{0x00FF00, 0x00FF00, 0x0000FF},
//			{0x00FF00, 0x00FF00, 0x0000FF}
//	};
//	test_sobel_operator(field_green_blue);
//	return EXIT_SUCCESS;

	if (argc < 2)
		rt_raise_error("sobel operator test require at least one arg!");

	t_sobel_img	img;
	int		img_num_channels;

	rt_sdl_init();
	img.data = (int*)stbi_load(argv[1], &img.width, &img.height, &img_num_channels, STBI_rgb_alpha);
	if (!img.data)
		rt_raise_error("error loading image!");
//	printf("img width: [%i], height: [%i]\n", img.width, img.height);
	process_img_sobel(&img);
	rt_render(&img, &render_sobel_corners);
	test_event_loop(NULL, NULL);
	return 0;
}
