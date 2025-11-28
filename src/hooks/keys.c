#include "minirt.h"

static void	ft_handle_movement_keys(t_data *data, mlx_key_data_t keydata)
{
	t_bool	pressed;

	pressed = (keydata.action == MLX_PRESS);
	if (keydata.key == MLX_KEY_W)
		data->keys[FTKEY_W] = pressed;
	else if (keydata.key == MLX_KEY_S)
		data->keys[FTKEY_S] = pressed;
	else if (keydata.key == MLX_KEY_A)
		data->keys[FTKEY_A] = pressed;
	else if (keydata.key == MLX_KEY_D)
		data->keys[FTKEY_D] = pressed;
	else if (keydata.key == MLX_KEY_C)
		data->keys[FTKEY_C] = pressed;
	else if (keydata.key == MLX_KEY_E)
		data->keys[FTKEY_E] = pressed;
}

static void	ft_handle_toggle_keys(t_data *data, mlx_key_data_t keydata)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_P)
	{
		data->flags[FISHEYE] = !data->flags[FISHEYE];
		data->flags[NEED_RENDER] = TRUE;
	}
	else if (keydata.key == MLX_KEY_R)
	{
		data->flags[REFLECT] = !data->flags[REFLECT];
		data->flags[NEED_RENDER] = TRUE;
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_RELEASE)
		ft_handle_movement_keys(data, keydata);
	ft_handle_toggle_keys(data, keydata);
}
