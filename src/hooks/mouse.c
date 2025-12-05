#include "minirt.h"

void	ft_mouse_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_data	*data;

	(void)mods;
	data = param;
	if (button == MLX_MOUSE_BUTTON_RIGHT)
	{
		data->flags[RMB] = (action == MLX_PRESS);
		if (data->flags[RMB])
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
		else
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	}
}

void	ft_cursor_hook(double xpos, double ypos, void *param)
{
	t_data	*data;

	data = param;
	if (data->flags[RMB])
	{
		data->mouse_dx += xpos - data->last_pos[X];
		data->mouse_dy -= ypos - data->last_pos[Y];
	}
	data->last_pos[X] = xpos;
	data->last_pos[Y] = ypos;
}
