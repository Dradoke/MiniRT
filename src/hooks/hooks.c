#include "minirt.h"

static void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

static void	on_resize(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = param;
	if (width <= 0 || height <= 0)
		return ;
	mlx_resize_image(data->img, width, height);
	render_image(data->sphere, data->img);
}

void	ft_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, &ft_key_hook, data);
	mlx_resize_hook(data->mlx, &render_image, data);
}
