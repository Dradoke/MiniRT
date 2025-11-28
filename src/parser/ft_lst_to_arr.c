#include "minirt.h"

static void	add_light(t_node *node, t_scene *scene)
{
	static int	i = 0;

	scene->light[i++] = node->u_data.point_light;
}

static void	add_mesh(t_node *node, t_scene *scene)
{
	static int	i = 0;

	scene->mesh[i].type = node->type;
	ft_memcpy(&scene->mesh[i].u_data, &node->u_data,
		sizeof(scene->mesh[i].u_data));
	i++;
}

static void	process_camera(t_node *node, t_scene *scene)
{
	t_vec3	dir;

	scene->cam = node->u_data.cam;
	build_transform(node, &scene->cam.matrix[NORMAL],
		&scene->cam.matrix[INVERTED]);
	dir = vec3_normalize(node->u_data.cam.direction);
	scene->cam.direction.x = -asin(dir.y);
	scene->cam.direction.y = atan2(dir.x, dir.z);
	scene->cam.direction.z = 0;
}

static void	process_node(t_node *node, t_scene *scene)
{
	if (node->type == A)
		scene->ambient_light = node->u_data.ambient_light;
	if (node->type == C)
		process_camera(node, scene);
	if (node->type == L)
		add_light(node, scene);
	if (node->type >= SP && node->type <= TR)
		add_mesh(node, scene);
}

t_bool	ft_lst_to_arr(t_data *data)
{
	t_list	*lst;
	t_scene	*scene;

	scene = &data->scene;
	lst = data->parse_list;
	scene->light = ft_calloc(scene->obj_count[LIGHT]
			* sizeof(t_point_light));
	scene->mesh = ft_calloc(scene->obj_count[MESH] * sizeof(t_mesh));
	while (lst)
	{
		process_node(lst->content, scene);
		lst = lst->next;
	}
	return (TRUE);
}
