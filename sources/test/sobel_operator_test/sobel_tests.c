#include "test_header.h"
#include "sobel_operator_tests.h"

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

void		run_sobel_tests(void)
{
	int field[3][3];

	prepare_test_field(0xFF0000, 0x0000FF, field);
	test_sobel_operator(field);

	prepare_test_field(0x00FF00, 0x0000FF, field);
	test_sobel_operator(field);

	prepare_test_field(0x737300, 0x750075, field);
	test_sobel_operator(field);
}
