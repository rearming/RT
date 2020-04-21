#ifndef SOBEL_OPERATOR_TESTS_H
# define SOBEL_OPERATOR_TESTS_H

typedef struct	s_sobel_img
{
	int			*data;
	int			width;
	int			height;
	int			num_channels;
}				t_sobel_img;

const float		kernel_x[3][3];
const float		kernel_y[3][3];

#define X_AXIS 0
#define Y_AXIS 1

void		process_img_sobel(t_sobel_img *img);
float		sobel_process_pixel(t_sobel_img *img, int img_x, int img_y, int axis);
int			get_sobel_color(float weigth);

#endif
