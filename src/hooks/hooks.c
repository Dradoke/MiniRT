#include "minirt.h"

static void	ft_resize_hook(int32_t width, int32_t height, void *param)
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

static t_bool	ft_has_movement(t_data *data)
{
	return (data->mouse_dx != 0 || data->mouse_dy != 0
		|| data->keys[FTKEY_W] || data->keys[FTKEY_S]
		|| data->keys[FTKEY_A] || data->keys[FTKEY_D]);
}

void	ft_render_pass(t_data *data, t_ui16 block_size)
{
	if (!mlx_resize_image(data->img, data->mlx->width, data->mlx->height))
		return ;
	data->block_size = block_size;
	ft_render(data);
}

static void	ft_loop_hook(void *param)
{
	t_data	*data;
	t_bool	is_moving;
	double	current_time;

	data = param;
	is_moving = ft_has_movement(data);
	ft_cam_movement(data);
	current_time = mlx_get_time();
	if (current_time - data->last_resize_time < RESIZE_DEBOUNCE_TIME)
		return ;
	if (is_moving || data->flags[NEED_RENDER])
	{
		ft_render_pass(data, MAX_BLOCK_SIZE);
		data->flags[NEED_RENDER] = FALSE;
		data->flags[IS_RENDERING] = FALSE;
	}
	else if (data->keys[FTKEY_E] && !data->flags[IS_RENDERING])
	{
		ft_render_pass(data, 1);
		data->flags[IS_RENDERING] = TRUE;
	}
}

void	ft_hooks(t_data *data)
{
	mlx_mouse_hook(data->mlx, &ft_mouse_hook, data);
	mlx_cursor_hook(data->mlx, &ft_cursor_hook, data);
	mlx_key_hook(data->mlx, &ft_key_hook, data);
	mlx_resize_hook(data->mlx, &ft_resize_hook, data);
	mlx_loop_hook(data->mlx, &ft_loop_hook, data);
}
