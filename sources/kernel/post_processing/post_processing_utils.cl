
bool			get_pixel(__global const int *img_data, float3 *out_pixel, int x, int y)
{
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		*out_pixel = get_float3_color(img_data[x + y * WIN_WIDTH]);
		return true;
	}
	return false;
}
