#include "rt.h"
#include "rt_math_utils.h"
#include <time.h>

bool		rt_camera_changed(t_camera *camera)
{
	static t_camera	previous_camera = (t_camera) {
		.pos = (cl_float3){{0, 0, 0}},
		.rotation = (cl_float3){{0, 0, 0}},
		.focal_distance = 0.0f,
		.aperture = 0.0f
	};
	static time_t		prev_time = NOT_SET;
	const time_t		current_time = time(NULL);
	bool				is_changed;

	is_changed = !rt_float3_equals(previous_camera.pos, camera->pos)
				 || !rt_float3_equals(previous_camera.rotation, camera->rotation)
				 || previous_camera.focal_distance != camera->focal_distance
				 || previous_camera.aperture != camera->aperture;
	if (prev_time == NOT_SET)
		prev_time = current_time;
	if (current_time != prev_time)
		previous_camera = *camera;
	if (is_changed)
	{
		previous_camera = *camera;
		prev_time = current_time;
	}
	return (is_changed);
}
