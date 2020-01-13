__kernel void	test_kernel(
		__constant int *int_arr,
		__constant t_point *point_arr,
		__global int *img_ptr)
{
	int g_id = get_global_id(0);

	for (int i = 0; i < 20; ++i)
	{
		printf("%d: [%d] ", i, int_arr[i]);
	}
	printf("\n");

	for (int j = 0; j < 10; ++j)
	{
		printf("%d: x: [%d] y: [%d] z: [%d] color: [%s]\n",
				j, point_arr[j].x, point_arr[j].y, point_arr[j].z, point_arr[j].color.value == COL_GREEN ? "COL_GREEN" : "COL_GREY");
	}
	printf("\n");

}