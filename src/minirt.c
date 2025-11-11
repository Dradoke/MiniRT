#include "minirt.h"

static void	ft_clean_data(t_data *data)
{
	
}

static void	ft_clean_end(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	ft_clean_data(data);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (EXIT_FAILURE);
	data = ft_calloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	ft_parser(data, av[1]);
	ft_mlx_init(data);
	ft_render(data);
	ft_hooks(data);
	mlx_loop(data->mlx);
	ft_clean_end(data);
	return (EXIT_SUCCESS);
}
