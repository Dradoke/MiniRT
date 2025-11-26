#include "minirt.h"

static void	rebuild_matrix(t_data *data)
{
	t_mat4	rot_y;
	t_mat4	rot_x;
	t_mat4	final;
	t_vec3	pos;

	mat4_extract_position(&pos, data->scene.cam.matrix[NORMAL]);
	mat4_rotation_y(&rot_y, data->scene.cam.direction.y);
	mat4_rotation_axis(&rot_x, (t_vec3){{1, 0, 0}}, data->scene.cam.direction.x);
	mat4_multiply(&final, rot_y, rot_x);
	mat4_set_position(&final, pos);
	ft_memcpy(data->scene.cam.matrix[NORMAL], final, sizeof(t_mat4));
}

static void	apply_mouse_rotation(t_data *data)
{
	if (data->mouse_dx == 0 && data->mouse_dy == 0)
		return ;
	data->scene.cam.direction.y -= data->mouse_dx * CAM_SENSI;
	data->scene.cam.direction.x += data->mouse_dy * CAM_SENSI;
	data->scene.cam.direction.z = 0;
	if (data->scene.cam.direction.x > 1.5)
		data->scene.cam.direction.x = 1.5;
	if (data->scene.cam.direction.x < -1.5)
		data->scene.cam.direction.x = -1.5;
	rebuild_matrix(data);
}

static t_vec3	get_standing_movement(t_data *data)
{
	t_vec3	move;
	t_vec3	fwd_ground;
	t_vec3	right;

	move = (t_vec3){{0, 0, 0}};
	fwd_ground = (t_vec3){{data->scene.cam.matrix[NORMAL][0][2], 0,
		data->scene.cam.matrix[NORMAL][2][2]}};
	fwd_ground = vec3_normalize(fwd_ground);
	right = vec3_normalize(vec3_cross(fwd_ground, (t_vec3){{0, 1, 0}}));
	if (data->keys[FTKEY_W])
		move = vec3_add(move, vec3_scale(fwd_ground, MOVE_SPEED));
	if (data->keys[FTKEY_S])
		move = vec3_add(move, vec3_scale(fwd_ground, -MOVE_SPEED));
	if (data->keys[FTKEY_D])
		move = vec3_add(move, vec3_scale(right, MOVE_SPEED));
	if (data->keys[FTKEY_A])
		move = vec3_add(move, vec3_scale(right, -MOVE_SPEED));
	return (move);
}

static t_vec3	get_plane_movement(t_data *data)
{
	t_vec3	move;
	t_vec3	fwd;

	move = (t_vec3){{0, 0, 0}};
	fwd = (t_vec3){{data->scene.cam.matrix[NORMAL][0][2],
		data->scene.cam.matrix[NORMAL][1][2],
		data->scene.cam.matrix[NORMAL][2][2]}};
	if (data->keys[FTKEY_W])
		move = vec3_add(move, vec3_scale(fwd, MOVE_SPEED));
	if (data->keys[FTKEY_S])
		move = vec3_add(move, vec3_scale(fwd, -MOVE_SPEED));
	return (move);
}

static void	apply_roll_rotation(t_data *data)
{
	t_mat4	rot_roll;
	t_mat4	temp;
	t_vec3	pos;
	t_vec3	fwd;
	t_f32	angle;

	angle = 0.0f;
	if (data->keys[FTKEY_A])
		angle = ROLL_SPEED;
	if (data->keys[FTKEY_D])
		angle = -ROLL_SPEED;
	if (angle == 0.0f)
		return ;
	fwd = (t_vec3){{data->scene.cam.matrix[NORMAL][0][2],
		data->scene.cam.matrix[NORMAL][1][2],
		data->scene.cam.matrix[NORMAL][2][2]}};
	mat4_rotation_axis(&rot_roll, fwd, angle);
	mat4_extract_position(&pos, data->scene.cam.matrix[NORMAL]);
	mat4_set_position(&data->scene.cam.matrix[NORMAL], (t_vec3){{0, 0, 0}});
	mat4_multiply(&temp, rot_roll, data->scene.cam.matrix[NORMAL]);
	ft_memcpy(data->scene.cam.matrix[NORMAL], temp, sizeof(t_mat4));
	mat4_set_position(&data->scene.cam.matrix[NORMAL], pos);
}

static void	apply_translation(t_data *data, t_vec3 move)
{
	if (vec3_length_sq(move) < 0.0001f)
		return ;
	data->scene.cam.matrix[NORMAL][0][3] += move.x;
	data->scene.cam.matrix[NORMAL][1][3] += move.y;
	data->scene.cam.matrix[NORMAL][2][3] += move.z;
}

static void	toggle_camera_mode(t_data *data)
{
	static t_bool	was_pressed = FALSE;

	if (data->keys[FTKEY_C] && !was_pressed)
	{
		if (data->scene.cam.mode == STANDING)
			data->scene.cam.mode = PLANE;
		else
			data->scene.cam.mode = STANDING;
		was_pressed = TRUE;
	}
	else if (!data->keys[FTKEY_C])
		was_pressed = FALSE;
}

void	ft_cam_movement(t_data *data)
{
	t_vec3	move;

	toggle_camera_mode(data);
	apply_mouse_rotation(data);
	if (data->scene.cam.mode == STANDING)
		move = get_standing_movement(data);
	else
	{
		move = get_plane_movement(data);
		apply_roll_rotation(data);
	}
	apply_translation(data, move);
	data->mouse_dx = 0.0;
	data->mouse_dy = 0.0;
}
