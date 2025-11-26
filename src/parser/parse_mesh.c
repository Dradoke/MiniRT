#include "minirt.h"

static t_bool	parse_sphere(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = SP;
	if (!parse_vec3(token[1], &node->u_data.sphere.location)
		|| !parse_size(token[2], &node->u_data.sphere.diameter)
		|| !parse_color(token[3], &node->u_data.sphere.color))
	{
		free(node);
		return (FALSE);
	}
	ft_lstadd_back(&data->parse_list, ft_lstnew(node));
	return (TRUE);
}

static t_bool	parse_plane(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = PL;
	if (!parse_vec3(token[1], &node->u_data.plane.location)
		|| !parse_normal_vec3(token[2], &node->u_data.plane.direction)
		|| !parse_color(token[3], &node->u_data.plane.color))
	{
		free(node);
		return (FALSE);
	}
	ft_lstadd_back(&data->parse_list, ft_lstnew(node));
	return (TRUE);
}

static t_bool	parse_cylinder(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = CY;
	if (!parse_vec3(token[1], &node->u_data.cylinder.location)
		|| !parse_normal_vec3(token[2], &node->u_data.cylinder.direction)
		|| !parse_size(token[3], &node->u_data.cylinder.diameter)
		|| !parse_size(token[4], &node->u_data.cylinder.height)
		|| !parse_color(token[5], &node->u_data.cylinder.color))
	{
		free(node);
		return (FALSE);
	}
	ft_lstadd_back(&data->parse_list, ft_lstnew(node));
	return (TRUE);
}

static t_bool	parse_triangle(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = TR;
	if (!parse_vec3(token[1], &node->u_data.triangle.vertex1)
		|| !parse_vec3(token[2], &node->u_data.triangle.vertex2)
		|| !parse_vec3(token[3], &node->u_data.triangle.vertex3)
		|| !parse_color(token[4], &node->u_data.triangle.color))
	{
		free(node);
		return (FALSE);
	}
	ft_lstadd_back(&data->parse_list, ft_lstnew(node));
	return (TRUE);
}

t_bool	parse_mesh(t_data *data, char **token)
{
	if (!ft_strcmp(token[0], "sp"))
		return (parse_sphere(data, token));
	if (!ft_strcmp(token[0], "pl"))
		return (parse_plane(data, token));
	if (!ft_strcmp(token[0], "cy"))
		return (parse_cylinder(data, token));
	if (!ft_strcmp(token[0], "tr"))
		return (parse_triangle(data, token));
	return (FALSE);
}
