float3		mix_avg_colors(float3 col_prev, float3 col_new, int samples)
{
	if (samples <= 1)
		return (col_new);
	const float		t = (float)1.0f / (samples);
	return mix(col_prev, col_new, t);
}

float3		mix_colors(float3 col1, float3 col2, float t)
{
	return mix(col1, col2, t);
}

float3		get_float3_color(int hex_color)
{
	t_color			color = { hex_color };

	return (float3)(
		(float)color.rgb.r / 255.0f,
		(float)color.rgb.g / 255.0f,
		(float)color.rgb.b / 255.0f);
}

float		color_energy(float3 color)
{
	return dot(color, 1.0f / 3.0f);
}

int			get_int_color(float3 color)
{
	t_color		result;

	result.rgb.a = 255;
	result.rgb.r = color.x * 255;
	result.rgb.g = color.y * 255;
	result.rgb.b = color.z * 255;
	return (result.value);
}

float3			correct_hdr(float gamma, float exposure, float3 hdr_color)
{
	float3	mapped = (float3)(1.0f) - exp(-hdr_color * exposure);
	mapped = pow(mapped, (float3)(1.0f / gamma));

	return mapped;
}

/*
int         get_texture_color(
		int2 pos,
		__constant float *texture_list,
		__constant t_texture_info *texture_info
		)
{
//	if (pos.x < texture_info->width && pos.y < texture_info->height)
//	{
//	return
//		texture_list[(pos.x + pos.y * texture_info->width) + 0] |
//		texture_list[(pos.x + pos.y * texture_info->width) + 1] |
//		texture_list[(pos.x + pos.y * texture_info->width) + 2];
//
//	}
}*/
