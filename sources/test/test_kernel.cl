t_color		mix_avg_color(t_color start, t_color end, int samples)
{
	t_color			avg;
	const float		t = (float) 1 / (samples + 1);

	avg.rgb.r = mix((float) start.rgb.r, (float) end.rgb.r, t);
	avg.rgb.g = mix((float) start.rgb.g, (float) end.rgb.g, t);
	avg.rgb.b = mix((float) start.rgb.b, (float) end.rgb.b, t);
	avg.rgb.a = 255;
	return (avg);
}

__kernel void	test_kernel(
		__global int *int_arr,
		__constant t_point *point_arr,
		__global int *img_ptr)
{
	int			g_id = get_global_id(0);
	img_ptr[g_id] = int_arr[0] == 0 ? COL_BLUE : img_ptr[g_id];

	t_color		color;
	color.value = img_ptr[g_id];
	img_ptr[g_id] = mix_avg_color(color, (t_color){{COL_GREEN}}, int_arr[0] + 2).value;

	if (g_id + 1 == WIN_WIDTH * WIN_HEIGHT)
		int_arr[0] += 1;
	g_id == 1 ? printf("0x%x\n", img_ptr[g_id]) : 0;
}