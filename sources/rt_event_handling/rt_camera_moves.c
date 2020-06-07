#include "rt.h"
#include "rt_math_utils.h"
#include "rt_events.h"

static inline void	move_forward(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z += MOVE_SPEED * cosf(rotation_rad.y);
	camera->pos.x += MOVE_SPEED * sinf(rotation_rad.y);
}

static inline void	move_backward(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z -= MOVE_SPEED * cosf(rotation_rad.y);
	camera->pos.x -= MOVE_SPEED * sinf(rotation_rad.y);
}

static inline void	move_left(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z += SIDE_MOVE_SPEED * cosf(rotation_rad.y - (float)M_PI / 2);
	camera->pos.x += SIDE_MOVE_SPEED * sinf(rotation_rad.y - (float)M_PI / 2);
}

static inline void	move_right(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z += SIDE_MOVE_SPEED * cosf(rotation_rad.y + (float)M_PI / 2);
	camera->pos.x += SIDE_MOVE_SPEED * sinf(rotation_rad.y + (float)M_PI / 2);
}

bool				rt_camera_move(t_camera *camera, uint32_t events)
{
	const cl_float3		cam_rotation_rad = rt_degree_to_rad(camera->rotation);

	if (events & EVENT_W)
		move_forward(camera, cam_rotation_rad);
	if (events & EVENT_A)
		move_left(camera, cam_rotation_rad);
	if (events & EVENT_S)
		move_backward(camera, cam_rotation_rad);
	if (events & EVENT_D)
		move_right(camera, cam_rotation_rad);
	if (events & EVENT_SPACE)
		camera->pos.y += FLY_SPEED;
	if (events & EVENT_LSHIFT)
		camera->pos.y -= FLY_SPEED;
	return (events);
}
