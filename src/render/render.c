/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_fill_block(t_data *data, t_ui16 block_size, t_ui32 color)
{
	t_i32		i;
	t_i32		j;

	j = 0;
	while (j < block_size && (data->screen[Y] + j) < data->mlx->height)
	{
		i = 0;
		while (i < block_size && (data->screen[X] + i) < data->mlx->width)
		{
			mlx_put_pixel(data->img, data->screen[X] + i,
				data->screen[Y] + j, color);
			i++;
		}
		j++;
	}
}

static void	render_at_size(t_data *data, t_ray *ray, t_i32 block_size)
{
	data->screen[Y] = 0;
	while (data->screen[Y] < data->mlx->height)
	{
		data->screen[X] = 0;
		while (data->screen[X] < data->mlx->width)
		{
			if (data->flags[FISHEYE])
				fisheye(data, ray, data->screen[X] + block_size
					/ 2, data->screen[Y] + block_size / 2);
			else
				perspective(data, ray, data->screen[X] + block_size
					/ 2, data->screen[Y] + block_size / 2);
			ft_fill_block(data, block_size, ft_rgba_to_uint(
					trace_ray(*ray, data->scene, MAX_DEPTH, data->flags)));
			data->screen[X] += block_size;
		}
		data->screen[Y] += block_size;
	}
}

t_bool	ft_render(t_data *data)
{
	t_ray		ray;

	if (data->block_size < 1)
		return (FALSE);
	ray.origin.x = data->scene.cam.matrix[NORMAL][0][3];
	ray.origin.y = data->scene.cam.matrix[NORMAL][1][3];
	ray.origin.z = data->scene.cam.matrix[NORMAL][2][3];
	render_at_size(data, &ray, data->block_size);
	return (TRUE);
}
