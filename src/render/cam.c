/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	apply_mouse_rotation_standing(t_data *data)
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

void	apply_plane_rotation(t_data *data, t_vec3 axis, t_f32 angle)
{
	t_mat4	rot;
	t_mat4	temp;
	t_vec3	pos;

	if (angle == 0.0f)
		return ;
	mat4_rotation_axis(&rot, axis, angle);
	mat4_extract_position(&pos, data->scene.cam.matrix[NORMAL]);
	mat4_set_position(&data->scene.cam.matrix[NORMAL], (t_vec3){{0, 0, 0}});
	mat4_multiply(&temp, rot, data->scene.cam.matrix[NORMAL]);
	ft_memcpy(data->scene.cam.matrix[NORMAL], temp, sizeof(t_mat4));
	mat4_set_position(&data->scene.cam.matrix[NORMAL], pos);
}

static void	apply_mouse_rotation_plane(t_data *data)
{
	t_vec3	right;
	t_vec3	up;

	if (data->mouse_dx == 0 && data->mouse_dy == 0)
		return ;
	right = (t_vec3){{data->scene.cam.matrix[NORMAL][0][0],
		data->scene.cam.matrix[NORMAL][1][0],
		data->scene.cam.matrix[NORMAL][2][0]}};
	up = (t_vec3){{data->scene.cam.matrix[NORMAL][0][1],
		data->scene.cam.matrix[NORMAL][1][1],
		data->scene.cam.matrix[NORMAL][2][1]}};
	apply_plane_rotation(data, right, data->mouse_dy * CAM_SENSI);
	apply_plane_rotation(data, up, -data->mouse_dx * CAM_SENSI);
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
	if (data->scene.cam.mode == STANDING)
	{
		apply_mouse_rotation_standing(data);
		move = get_standing_movement(data);
	}
	else
	{
		apply_mouse_rotation_plane(data);
		move = get_plane_movement(data);
		apply_roll_rotation(data);
	}
	apply_translation(data, move);
	data->mouse_dx = 0.0;
	data->mouse_dy = 0.0;
}
