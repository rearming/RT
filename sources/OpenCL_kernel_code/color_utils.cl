int			mix_avg_color(t_color col_prev, t_color col_new, int samples)
{
	if (samples <= 1)
		return (col_new.value);
	t_color			avg;
	const float		t = (float) 1 / (samples);

	avg.rgb.r = mix((float) col_prev.rgb.r, (float) col_new.rgb.r, t);
	avg.rgb.g = mix((float) col_prev.rgb.g, (float) col_new.rgb.g, t);
	avg.rgb.b = mix((float) col_prev.rgb.b, (float) col_new.rgb.b, t);
	avg.rgb.a = 255;
	return (avg.value);
}

t_color				change_color_intensity(t_color color, float intensity)
{
	t_color		result_color;

	intensity = clamp(intensity, 0.0f, 1.0f);
	result_color.rgb.a = color.rgb.a;
	result_color.rgb.r = color.rgb.r * intensity;
	result_color.rgb.g = color.rgb.g * intensity;
	result_color.rgb.b = color.rgb.b * intensity;
	return result_color;
}

// -> TODO разобраться с тем, чтобы свет только УВЕЛИЧИВАЛ яркость, а не уменьшал ее
// -> нужно ли?? ведь там где нет света яркость как раз должна быть 0, то есть черный
// -> а как тогда реализовать разные цвета света?? TODO!

t_color				change_color_intensity_colors(t_color target_color, t_color light_color)
{

//	target_color.rgb.r *= light_color.rgb.r ? (float)((float)light_color.rgb.r / 255) : 1;
//	target_color.rgb.g *= light_color.rgb.g ? (float)((float)light_color.rgb.g / 255) : 1;
//	target_color.rgb.b *= light_color.rgb.b ? (float)((float)light_color.rgb.b / 255) : 1;

//	target_color.rgb.r += clamp(int(target_color.rgb.r * (float)((float)light_color.rgb.r / 255)), 0, 255);
//	target_color.rgb.g += clamp(int(target_color.rgb.g * (float)((float)light_color.rgb.g / 255)), 0, 255);
//	target_color.rgb.b += clamp(int(target_color.rgb.b * (float)((float)light_color.rgb.b / 255)), 0, 255);

//	target_color.rgb.r += (float)target_color.rgb.r * (float)((float)light_color.rgb.r / 255);
//	target_color.rgb.g += (float)target_color.rgb.g * (float)((float)light_color.rgb.g / 255);
//	target_color.rgb.b += (float)target_color.rgb.b * (float)((float)light_color.rgb.b / 255);

	target_color.rgb.r *= ((float)light_color.rgb.r / 255);
	target_color.rgb.g *= ((float)light_color.rgb.g / 255);
	target_color.rgb.b *= ((float)light_color.rgb.b / 255);

//	if (target_color.rgb.r)
//		target_color.rgb.r *= ((float)light_color.rgb.r / 255);
//	if (target_color.rgb.g)
//		target_color.rgb.g *= ((float)light_color.rgb.g / 255);
//	if (target_color.rgb.b)
//		target_color.rgb.b *= ((float)light_color.rgb.b / 255);

	return target_color;
}
