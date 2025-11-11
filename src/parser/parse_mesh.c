#include "minirt.h"

static t_bool	parse_sphere(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = sp;
}

static t_bool	parse_plane(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = pl;
}

static t_bool	parse_cylinder(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = cy;
}

static t_bool	parse_triangle(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = tr;
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
