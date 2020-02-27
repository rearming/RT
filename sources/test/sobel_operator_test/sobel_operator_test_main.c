#include "test_header.h"
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

const int		kernel_x[3][3] = {
		{-1, 0, +1},
		{-2, 0, +2},
		{-1, 0, +1}
};

const int		kernel_y[3][3] = {
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

static inline int	sobel_get_pixel(t_sobel_img *img, int x, int y)
{
	if (x > 0 && y > 0 && x < img->width && y < img->height)
		return img->data[x + y * img->width];
	return 0;
}

static inline int	sobel_process_pixel(t_sobel_img *img, int x, int y, int axis)
{
	int		result = 0;

	int		k_x = 0;

	for (int i = x - 1; i <= x + 1; ++i)
	{
		int		k_y = 0;
		for (int j = y - 1; j < y + 1; ++j)
		{
			if (axis == X_AXIS)
				result += sobel_get_pixel(img, i, j) * kernel_x[k_y][k_x];
			else
				result += sobel_get_pixel(img, i, j) * kernel_y[k_y][k_x];
			k_y++;
		}
		k_x++;
	}
	return result;
}

void		process_img_sobel(t_sobel_img *img)
{
	int		*new_img = rt_safe_malloc(img->width * img->height * sizeof(int));

	for (int y = 0; y < img->height; ++y)
	{
		for (int x = 0; x < img->width; ++x)
		{
			int		x_sobel_value = sobel_process_pixel(img, x, y, X_AXIS);
			int		y_sobel_value = sobel_process_pixel(img, x, y, Y_AXIS);
//			new_img[x + y * img->width] = ;
			double weight = 0;
			if (x_sobel_value && y_sobel_value)
				weight = sqrt(x_sobel_value * x_sobel_value + y_sobel_value * y_sobel_value);
//			printf("weight: [%f]\n", weight);
			new_img[x + y * img->width] = (int)weight ? 0xFFFFFF : 0x000000;
		}
	}
	for (int i = 0; i < img->width * img->height; ++i)
	{
		img->data[i] = new_img[i];
	}
	free(new_img);
}

t_sdl		g_sdl;
t_opencl	g_opencl;
int			*g_img_data;

int		main(int argc, char **argv)
{
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
