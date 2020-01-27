#include "test_header.h"

double	lerp(double start, double end, double t)
{
	return (1 - t) * start + t * end;
}

double	avg(double *arr, int arr_size)
{
	double		avg = 0;
	for (int i = 0; i < arr_size; ++i)
	{
		avg += arr[i];
	}
	return (avg / arr_size);
}

double	lerp_avg(double *test_arr, int arr_size)
{
	double	avg;

	avg = test_arr[0];
	for (int i = 1; i < arr_size; ++i)
	{
		double t = (double)1 / (i + 1);
		avg = lerp(avg, test_arr[i], t);
	}
	return (avg);
}

void		test_lerp_avg(void)
{
	//	double		test_arr[] = {3, 3, 9, 24, 2};
//	int			test_arr_size = sizeof(test_arr) / sizeof(double);
	int			test_arr_size = 1000;
	double		*test_arr = test_get_double_arr(test_arr_size);

	printf("sizeof arr: [%i]\n", test_arr_size);
	printf("avg: [%f], lerp avg: [%f]\n", avg(test_arr, test_arr_size), lerp_avg(test_arr, test_arr_size));
}
