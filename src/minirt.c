#include "minirt.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (EXIT_FAILURE);
	data = ft_calloc(sizeof(t_data));
	if (!data)
		ft_error(data, EXIT_FAILURE, FTERR_ALLOC);
	ft_parser(data, av[1]);
	see_data(data);
	return (ft_clean_all(data), EXIT_SUCCESS);
}
