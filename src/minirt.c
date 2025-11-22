#include "minirt.h"

// static void	ft_mlx_init(t_data	*data)
// {
// 	data->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
// 	if (!data->mlx)
// 		ft_error(data, EXIT_FAILURE, FTERR_MLX);
// 	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
// 	if (!data->img || mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
// 		ft_error(data, EXIT_FAILURE, FTERR_MLX);
// }

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (EXIT_FAILURE);
	data = ft_calloc(sizeof(t_data));
	if (!data)
		ft_error(data, EXIT_FAILURE, FTERR_ALLOC);
	ft_printfd(1, "START COUNT LIGHT: at %p is %d\n", &(data->scene.obj_count[LIGHT]), data->scene.obj_count[LIGHT]);
	ft_printfd(1, "START COUNT MESH: at %p is %d\n", &(data->scene.obj_count[MESH]), data->scene.obj_count[MESH]);
	if (!ft_parser(data, av[1]))
		ft_error(data, EXIT_FAILURE, FTERR_PARSE);
	see_data(data);
	// ft_mlx_init(data);
	// ft_render(data);
	return (ft_clean_all(data), EXIT_SUCCESS);
}
