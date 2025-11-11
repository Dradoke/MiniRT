#include "minirt.h"

static void	ft_clean_all(t_data	*data)
{
	if (!data)
		return ;
	if (data->parse_list)
		ft_lstclear(&data->parse_list, free);
}

t_bool	ft_error(t_data *data, int error_code, char *error_message)
{
	ft_printfd(2, "%s", error_message);
	ft_clean_all(data);
	exit(error_code);
}
