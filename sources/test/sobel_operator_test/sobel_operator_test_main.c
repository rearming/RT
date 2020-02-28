#include "test_header.h"
#include "sobel_operator_tests.h"
#include <rt_math_utils.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

int			switch_channels(int color)
{
	t_color	result = {color};
	t_color	base_color = {color};

	result.rgb.r = base_color.rgb.b;
	result.rgb.g = base_color.rgb.g;
	result.rgb.b = base_color.rgb.r;
	result.rgb.a = 255;
	return result.value;
}

t_sobel_img		init_sobel_test(char *img_name)
{
	t_sobel_img	img;
	int		img_num_channels;

	rt_sdl_init();
	img.data = (int*)stbi_load(img_name, &img.width, &img.height, &img_num_channels, STBI_rgb_alpha);
//	printf("img width: [%i], height: [%i]\n", img.width, img.height);
	if (!img.data)
		rt_raise_error("error loading image!");
	for (int y = 0; y < img.height; ++y)
	{
		for (int x = 0; x < img.width; ++x)
		{
			img.data[x + y * img.width] = switch_channels(img.data[x + y * img.width]);
		}
	}
	return img;
}

t_sdl		g_sdl;
t_opencl	g_opencl;
int			*g_img_data;

int		main(int argc, char **argv)
{
	if (argc < 2)
		rt_raise_error("sobel operator test require at least one arg!");

	t_sobel_img		img = init_sobel_test(argv[1]);
	process_img_sobel(&img);

	rt_render(&img, &render_sobel_corners);
	test_event_loop(NULL, NULL);
	return 0;
}
