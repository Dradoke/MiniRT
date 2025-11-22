#include "minirt.h"

static void	rebuild_cam_matrix(t_cam *cam, t_vec3 right, t_vec3 up, t_vec3 fwd)
{
	cam->matrix[NORMAL][0][0] = right.x;
	cam->matrix[NORMAL][1][0] = right.y;
	cam->matrix[NORMAL][2][0] = right.z;
	cam->matrix[NORMAL][0][1] = up.x;
	cam->matrix[NORMAL][1][1] = up.y;
	cam->matrix[NORMAL][2][1] = up.z;
	cam->matrix[NORMAL][0][2] = fwd.x;
	cam->matrix[NORMAL][1][2] = fwd.y;
	cam->matrix[NORMAL][2][2] = fwd.z;
}

static void	handle_mouse_rotation(t_data *data)
{
	t_vec3	r;
	t_vec3	u;
	t_vec3	f;
	double	yaw;
	double	pitch;

	if (data->mouse_dx == 0 && data->mouse_dy == 0)
		return ;
	yaw = -data->mouse_dx * CAM_SENSI;
	pitch = -data->mouse_dy * CAM_SENSI;
	r = (t_vec3){{data->scene.cam.matrix[NORMAL][0][0],
		data->scene.cam.matrix[NORMAL][1][0], data->scene.cam.matrix[NORMAL][2][0]}};
	u = (t_vec3){{data->scene.cam.matrix[NORMAL][0][1],
		data->scene.cam.matrix[NORMAL][1][1], data->scene.cam.matrix[NORMAL][2][1]}};
	f = (t_vec3){{data->scene.cam.matrix[NORMAL][0][2],
		data->scene.cam.matrix[NORMAL][1][2], data->scene.cam.matrix[NORMAL][2][2]}};
	f = vec3_rotate(f, (t_vec3){{0, 1, 0}}, yaw);
	r = vec3_rotate(r, (t_vec3){{0, 1, 0}}, yaw);
	f = vec3_rotate(f, r, pitch);
	u = vec3_rotate(u, r, pitch);
	rebuild_cam_matrix(&data->scene.cam, vec3_normalize(r),
		vec3_normalize(u), vec3_normalize(f));
}

static void	handle_standing_movement(t_data *data)
{
	t_vec3	move;
	t_vec3	forward_ground;
	t_vec3	right_ground;

	move = (t_vec3){{0, 0, 0}};
	forward_ground = (t_vec3){{data->scene.cam.matrix[NORMAL][0][2], 0,
		data->scene.cam.matrix[NORMAL][2][2]}};
	forward_ground = vec3_normalize(forward_ground);
	right_ground = vec3_normalize(vec3_cross(forward_ground, (t_vec3){{0, 1, 0}}));
	if (data->keys[FTKEY_W])
		move = vec3_add(move, vec3_scale(forward_ground, MOVE_SPEED));
	if (data->keys[FTKEY_S])
		move = vec3_add(move, vec3_scale(forward_ground, -MOVE_SPEED));
	if (data->keys[FTKEY_D])
		move = vec3_add(move, vec3_scale(right_ground, MOVE_SPEED));
	if (data->keys[FTKEY_A])
		move = vec3_add(move, vec3_scale(right_ground, -MOVE_SPEED));
	data->scene.cam.matrix[NORMAL][0][3] += move.x;
	data->scene.cam.matrix[NORMAL][1][3] += move.y;
	data->scene.cam.matrix[NORMAL][2][3] += move.z;
}

static void	handle_plane_movement(t_data *data)
{
	t_vec3	move;
	t_vec3	r;
	t_vec3	u;
	t_vec3	f;

	move = (t_vec3){{0, 0, 0}};
	f = (t_vec3){{data->scene.cam.matrix[NORMAL][0][2],
		data->scene.cam.matrix[NORMAL][1][2], data->scene.cam.matrix[NORMAL][2][2]}};
	if (data->keys[FTKEY_W])
		move = vec3_add(move, vec3_scale(f, MOVE_SPEED));
	if (data->keys[FTKEY_S])
		move = vec3_add(move, vec3_scale(f, -MOVE_SPEED));
	data->scene.cam.matrix[NORMAL][0][3] += move.x;
	data->scene.cam.matrix[NORMAL][1][3] += move.y;
	data->scene.cam.matrix[NORMAL][2][3] += move.z;
	r = (t_vec3){{data->scene.cam.matrix[NORMAL][0][0],
		data->scene.cam.matrix[NORMAL][1][0], data->scene.cam.matrix[NORMAL][2][0]}};
	u = (t_vec3){{data->scene.cam.matrix[NORMAL][0][1],
		data->scene.cam.matrix[NORMAL][1][1], data->scene.cam.matrix[NORMAL][2][1]}};
	if (data->keys[FTKEY_A])
		rebuild_cam_matrix(&data->scene.cam, vec3_rotate(r, f, ROLL_SPEED),
			vec3_rotate(u, f, ROLL_SPEED), f);
	if (data->keys[FTKEY_D])
		rebuild_cam_matrix(&data->scene.cam, vec3_rotate(r, f, -ROLL_SPEED),
			vec3_rotate(u, f, -ROLL_SPEED), f);
}

void	ft_cam_movement(t_data *data)
{
	if (data->keys[FTKEY_C] && !data->keys[FTKEY_C])
	{
		if (data->scene.cam.mode == STANDING)
			data->scene.cam.mode = PLANE;
		else
			data->scene.cam.mode = STANDING;
		data->keys[FTKEY_C] = true;
	}
	else if (!data->keys[FTKEY_C])
		data->keys[FTKEY_C] = false;
	handle_mouse_rotation(data);
	if (data->scene.cam.mode == STANDING)
		handle_standing_movement(data);
	else if (data->scene.cam.mode == PLANE)
		handle_plane_movement(data);
	data->mouse_dx = 0;
	data->mouse_dy = 0;
	data->flags[NEED_RENDER] = TRUE;
}
