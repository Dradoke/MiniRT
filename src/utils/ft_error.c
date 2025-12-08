/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (data->line)
		free(data->line);
	free(data);
	get_next_line(-1);
}

void	ft_clean_gnl(t_data *data)
{
	char	*gnl_line;

	if (data->fd_file <= 2)
		return ;
	gnl_line = get_next_line(data->fd_file);
	while (gnl_line)
	{
		free(gnl_line);
		gnl_line = get_next_line(data->fd_file);
	}
}

void	ft_error(t_data *data, int error_code, char *error_message)
{
	ft_printfd(2, "%s", error_message);
	ft_clean_gnl(data);
	ft_clean_all(data);
	exit(error_code);
}
