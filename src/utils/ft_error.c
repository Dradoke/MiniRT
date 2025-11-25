#include "minirt.h"

void	*safe_calloc(t_data *data, t_ui32 size)
{
	void	*alloc;

	alloc = ft_calloc(size);
	if (!alloc)
		ft_error(data, EXIT_FAILURE, FTERR_ALLOC);
	return (alloc);
}

void	ft_clean_all(t_data	*data)
{
	if (!data)
		return ;
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->parse_list)
		ft_lstclear(&data->parse_list, free);
	if (data->scene.light)
		free(data->scene.light);
	if (data->scene.mesh)
		free(data->scene.mesh);
	free(data);
}

void	ft_error(t_data *data, int error_code, char *error_message)
{
	ft_printfd(2, "%s", error_message);
	ft_clean_all(data);
	exit(error_code);
}
