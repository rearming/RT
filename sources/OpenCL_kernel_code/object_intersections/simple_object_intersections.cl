void				ray_plane_intersect(
		float3 camera_pos,
		float3 ray_dir,
		float3 center,
		float3 normal,
		float *out_x1,
		float *out_x2)
{
	const float3	origin_center = camera_pos - center;

	*out_x1 = (-dot(origin_center, normal)) / dot(ray_dir, normal);
}

void				ray_sphere_intersect(
		float3 camera_pos,
		float3 ray_dir,
		__constant t_object *sphere,
		float *out_x1,
		float *out_x2)
{
//	const float3	origin_center = camera_pos - sphere->center;
//	float 			a, b, c, discriminant;
//
//	a = dot(ray_dir, ray_dir);
//	b = 2 * dot(origin_center, ray_dir);
//	c = dot(origin_center, origin_center) - sphere->radius * sphere->radius;
//	discriminant = b * b - 4 * a * c;
//	if (discriminant < 0)
//		return ;
//	float sqrt_discriminant = sqrt(discriminant);
//
//	*out_x1 = (-b + sqrt_discriminant) / (2 * a);
//	*out_x2 = (-b - sqrt_discriminant) / (2 * a);
}
