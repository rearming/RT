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
