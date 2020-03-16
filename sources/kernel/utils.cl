
float3			canvas_to_viewport(__global const t_camera *camera, float3 canvas_point)
{
	return (float3)
	(
		canvas_point.x * camera->viewport_width / WIN_WIDTH,
		canvas_point.y * camera->viewport_height / WIN_HEIGHT,
		camera->viewport_distance
	);
}

float3		reflect(float3 ray_dir, float3 normal)
{
	return ray_dir - 2 * dot(normal, ray_dir) * normal;
}

float3		convex_refract(float3 ray_dir, float3 normal, float refract_index)
{
	refract_index = 2.0f - refract_index;
	float normal_dot_ray = dot(normal, ray_dir);
	float3 refracted = (ray_dir * refract_index - normal * (-normal_dot_ray + refract_index * normal_dot_ray));
	return refracted;
}

float3		concave_refract(float3 ray_dir, float3 normal, float refract_index)
{
	float	normal_dot_ray = dot(normal, ray_dir);

	float k = 1.0 - refract_index * refract_index * (1.0 - normal_dot_ray * normal_dot_ray);
	if (k < 0.0)
		return (float3)(0);
	else
		return refract_index * ray_dir - (refract_index * normal_dot_ray + sqrt(k)) * normal;
}

bool		isset(int value)
{
	return (value != NOT_SET);
}

float		saturate(float value)
{
	return clamp(value, 0.0f, 1.0f);
}

float3		saturate_float3(float3 value)
{
	return clamp(value, 0.0f, 1.0f);
}

bool		ray_has_energy(t_ray *ray)
{
	return ray->energy.x > 0 || ray->energy.y > 0 || ray->energy.z > 0;
}

int3		get_img_point(int global_id)
{
	return (int3)(global_id % WIN_WIDTH, global_id / WIN_WIDTH, 0);
}

void			correct_img_point(float3 *img_point)
{
	img_point->x -= WIN_WIDTH / 2;
	img_point->y -= WIN_HEIGHT / 2;
	img_point->y = -img_point->y;
}

t_ray			get_ray(float3 img_point, __global const t_camera *camera)
{
	t_ray		ray;

	correct_img_point(&img_point);
	ray.dir = fast_normalize(canvas_to_viewport(camera, img_point));
	rotate_point(&ray.dir, camera->rotation);
	ray.origin = camera->pos;
	ray.energy = (float3)(1.0f, 1.0f, 1.0f);
	return ray;
}

float3			correct_hdr(float gamma, float exposure, float3 hdr_color)
{
	float3	mapped = (float3)(1.0f) - exp(-hdr_color * exposure);
	mapped = pow(mapped, (float3)(1.0f / gamma));

	return mapped;
}
