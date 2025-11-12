#include "minirt.h"

static t_bool	parse_ambient_light(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = A;
	node->u_data.ambient_light.brightness = ft_atof(token[1]);
	if (node->u_data.ambient_light.brightness > 1.0
		|| node->u_data.ambient_light.brightness < 0.0)
		return (FALSE);
	if (!color_parser(token[2], &(node->u_data.ambient_light.color)))
		return (FALSE);
	return (TRUE);
}

static t_bool	parse_camera(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = C;
	if (!vec3_parser(token[1], &node->u_data.cam.location)
	|| !normal_vec3_parser(token[2], &node->u_data.cam.rotation)
	|| !aov_parser(token[3], &node->u_data.cam.aov))
	node->u_data.cam.aov = ft_atof(token[3]);
}

static t_bool	parse_point_light(t_data *data, char **token)
{
	t_node	*node;

	node = ft_calloc(sizeof(t_node));
	if (!node)
		return (FALSE);
	node->type = L;
}

t_bool	parse_unique(t_data *data, char **token)
{
	if (!ft_strcmp(token[0], "A"))
		return (parse_ambient_light(data, token));
	if (!ft_strcmp(token[0], "C"))
		return (parse_camera(data, token));
	if (!ft_strcmp(token[0], "L"))
		return (parse_point_light(data, token));
	return (FALSE);
}
