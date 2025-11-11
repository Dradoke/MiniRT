#include "minirt.h"

void	ft_mlx_init(t_data	*data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!data->mlx)
		ft_error();
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (!data->img || mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		ft_error();
}
