#include "minirt.h"

static void	ft_mlx_init(t_data	*data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!data->mlx)
		ft_error(data, EXIT_FAILURE, FTERR_MLX);
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (!data->img || mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		ft_error(data, EXIT_FAILURE, FTERR_MLX);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (EXIT_FAILURE);
	data = ft_calloc(sizeof(t_data));
	if (!data)
		ft_error(data, EXIT_FAILURE, FTERR_ALLOC);
	if (!ft_parser(data, av[1]))
		ft_error(data, EXIT_FAILURE, FTERR_PARSE);
	ft_mlx_init(data);
	ft_init_random_seed(&data->scene.seed);
	ft_render_pass(data, 1);
	data->flags[NEED_RENDER] = FALSE;
	ft_hooks(data);
	mlx_loop(data->mlx);
	return (ft_clean_all(data), EXIT_SUCCESS);
}
