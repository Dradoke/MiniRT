#include "minirt.h"

static void	ft_cursor_hook(double xpos, double ypos, void *param)
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

static void	ft_mouse_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_data	*data;

	(void)mods;
	data = param;
	if (button == MLX_MOUSE_BUTTON_RIGHT)
	{
		if (action == MLX_PRESS)
		{
			data->flags[RMB] = TRUE;
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
		}
		else if (action == MLX_RELEASE)
		{
			data->flags[RMB] = FALSE;
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		}
	}
}

static void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			data->keys[FTKEY_W] = (keydata.action == MLX_PRESS);
		if (keydata.key == MLX_KEY_S)
			data->keys[FTKEY_S] = (keydata.action == MLX_PRESS);
		if (keydata.key == MLX_KEY_A)
			data->keys[FTKEY_A] = (keydata.action == MLX_PRESS);
		if (keydata.key == MLX_KEY_D)
			data->keys[FTKEY_D] = (keydata.action == MLX_PRESS);
		if (keydata.key == MLX_KEY_C)
			data->keys[FTKEY_C] = (keydata.action == MLX_PRESS);
	}
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		data->flags[FISHEYE] = !data->flags[FISHEYE];
		data->flags[NEED_RENDER] = TRUE;
	}
}

static void	ft_resize(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = param;
	if (width <= 0 || height <= 0)
		return ;
	data->mlx->width = width;
	data->mlx->height = height;
	data->flags[NEED_RENDER] = TRUE;
	data->flags[IS_RENDERING] = FALSE;
	data->last_resize_time = mlx_get_time();
}

static void	ft_start_progressive_render(t_data *data)
{
	if (!mlx_resize_image(data->img, data->mlx->width, data->mlx->height))
		return ;
	data->block_size = 16;
	data->flags[NEED_RENDER] = FALSE;
	data->flags[IS_RENDERING] = TRUE;
}

static void	ft_loop_hook(void *param)
{
	t_data	*data;
	double	current_time;
	t_bool	has_input;

	data = param;
	has_input = (data->mouse_dx != 0 || data->mouse_dy != 0
			|| data->keys[FTKEY_W] || data->keys[FTKEY_S]
			|| data->keys[FTKEY_A] || data->keys[FTKEY_D]);
	ft_cam_movement(data);
	if (has_input)
	{
		data->flags[NEED_RENDER] = TRUE;
		data->flags[IS_RENDERING] = FALSE;
	}
	current_time = mlx_get_time();
	if (data->flags[NEED_RENDER]
		&& (current_time - data->last_resize_time > RESIZE_DEBOUNCE_TIME))
		ft_start_progressive_render(data);
	if (data->flags[IS_RENDERING])
	{
		ft_render(data);
		if (data->block_size > 1)
			data->block_size /= 2;
		else
			data->flags[IS_RENDERING] = FALSE;
	}
}

void	ft_hooks(t_data *data)
{
	data->flags[NEED_RENDER] = TRUE;
	data->flags[IS_RENDERING] = FALSE;
	data->last_resize_time = 0.0;
	data->block_size = 0;
	mlx_mouse_hook(data->mlx, &ft_mouse_hook, data);
	mlx_cursor_hook(data->mlx, &ft_cursor_hook, data);
	mlx_key_hook(data->mlx, &ft_key_hook, data);
	mlx_resize_hook(data->mlx, &ft_resize, data);
	mlx_loop_hook(data->mlx, &ft_loop_hook, data);
}
