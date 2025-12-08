/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:09:43 by mavander          #+#    #+#             */
/*   Updated: 2025/11/28 20:09:43 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bool	parse_ambient_light(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	ft_lstadd_back(&data->parse_list, ft_lstnew(node));
	node->type = A;
	if (!parse_brightness(token[1], &node->u_data.ambient_light.brightness)
		|| !parse_color(token[2], &node->u_data.ambient_light.color))
		return (FALSE);
	return (TRUE);
}

static t_bool	parse_camera(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	ft_lstadd_back(&data->parse_list, ft_lstnew(node));
	node->type = C;
	if (!parse_vec3(token[1], &node->u_data.cam.location)
		|| !parse_normal_vec3(token[2], &node->u_data.cam.direction)
		|| !parse_aov(token[3], &node->u_data.cam.aov))
		return (FALSE);
	return (TRUE);
}

static t_bool	parse_point_light(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = L;
	if (!parse_vec3(token[1], &node->u_data.point_light.location)
		|| !parse_brightness(token[2], &node->u_data.point_light.brightness)
		|| !parse_color(token[3], &node->u_data.point_light.color))
	{
		free(node);
		return (FALSE);
	}
	ft_lstadd_back(&data->parse_list, ft_lstnew(node));
	return (TRUE);
}

t_bool	parse_unique(t_data *data, char **token)
{
	if (!ft_strcmp(token[0], "A"))
		return (parse_ambient_light(data, token));
	if (!ft_strcmp(token[0], "C"))
		return (parse_camera(data, token));
	if (!ft_strcmp(token[0], "L"))
	{
		if (!parse_point_light(data, token))
			return (FALSE);
		(data->scene.obj_count[LIGHT])++;
		return (TRUE);
	}
	return (FALSE);
}
