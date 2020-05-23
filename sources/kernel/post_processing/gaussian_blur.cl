
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

float3			gauss_process_pixel(
		__global const int *img_data,
		int2 img_point,
		int blur_coeff)
{
	float	kernel_sum = 0;
	float3	result_color = 0;

	result_color += process_pixel_horizontal(img_data, img_point, blur_coeff, &kernel_sum);
	result_color += process_pixel_vertical(img_data, img_point, blur_coeff, &kernel_sum);
	result_color /= kernel_sum;

	return result_color;
}
