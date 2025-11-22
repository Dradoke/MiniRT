#include "minirt.h"

static void	compute_transform_matrices(t_node *node, t_mat4 *trans_m,
				t_mat4 *rot_m, t_mat4 *scale_m)
{
	t_vec3	scale_vec;
	t_vec3	trans_vec;
	t_f32	r;
	t_f32	h;

	trans_vec = node->u_data.sphere.location;
	/* mat4_* functions fill the output matrix via le premier argument (t_mat4 *) */
	mat4_translation(trans_m, trans_vec);
	mat4_identity(rot_m);
	if (node->type == SP)
	{
		r = node->u_data.sphere.diameter / 2.0f;
		scale_vec = (t_vec3){{r, r, r}};
	}
	else if (node->type == CY)
	{
		r = node->u_data.cylinder.diameter / 2.0f;
		h = node->u_data.cylinder.height / 2.0f;
		scale_vec = (t_vec3){{r, h, r}};
	}
	else
		scale_vec = (t_vec3){{1.0f, 1.0f, 1.0f}};
	mat4_scaling(scale_m, scale_vec);
}

static void	build_transform(t_node *node, t_mat4 *out_transform,
				t_mat4 *out_inv_transform)
{
	t_mat4	trans_m;
	t_mat4	rot_m;
	t_mat4	scale_m;
	t_mat4	inv_trans_m;
	t_mat4	inv_scale_m;

	compute_transform_matrices(node, &trans_m, &rot_m, &scale_m);
	mat4_translation(&inv_trans_m, (t_vec3){{
			-node->u_data.sphere.location.x,
			-node->u_data.sphere.location.y,
			-node->u_data.sphere.location.z}});
	mat4_scaling(&inv_scale_m, (t_vec3){{
			1.0f / scale_m[0][0],
			1.0f / scale_m[1][1],
			1.0f / scale_m[2][2]}});
	/* mat4_multiply(out, a, b) -> out = a * b
	   les fonctions prennent maintenant t_mat4 *out en premier argument */
	mat4_multiply(out_transform, rot_m, scale_m);
	mat4_multiply(out_transform, trans_m, *out_transform);
	mat4_multiply(out_inv_transform, rot_m, inv_trans_m);
	mat4_multiply(out_inv_transform, inv_scale_m, *out_inv_transform);
}

static void	add_light(t_node *node, t_scene *scene)
{
	static int	i = 0;

	scene->light[i++] = node->u_data.point_light;
}

static void	add_mesh(t_node *node, t_scene *scene)
{
	static int	i = 0;

	ft_printfd(1, RED"INDEX MESH:%d\n"RESET, i);
	scene->mesh[i].type = node->type;
	ft_memcpy(&scene->mesh[i].u_data, &node->u_data, sizeof(node->u_data));
	build_transform(node, &scene->mesh[i].transform,
		&scene->mesh[i].inv_transform);
	i++;
}

t_bool	ft_lst_to_arr(t_data *data)
{
	t_list	*lst;
	t_node	*node;
	t_scene	*scene;

	scene = &data->scene;
	lst = data->parse_list;
	ft_printfd(1, "\n");
	ft_printfd(1, "COUNT LIGHT: at %p is %d\n", &(scene->obj_count[LIGHT]), scene->obj_count[LIGHT]);
	ft_printfd(1, "COUNT MESH: at %p is %d\n", &(scene->obj_count[MESH]), scene->obj_count[MESH]);
	scene->light = ft_calloc(scene->obj_count[LIGHT] * sizeof(t_point_light));
	scene->mesh = ft_calloc(scene->obj_count[MESH] * sizeof(t_mesh));
	while (lst)
	{
		node = lst->content;
		if (node->type == A)
			scene->ambient_light = node->u_data.ambient_light;
		if (node->type == C)
			scene->cam = node->u_data.cam;
		if (node->type == L)
			add_light(node, scene);
		if (node->type >= SP && node->type <= TR)
			add_mesh(node, scene);
		lst = lst->next;
	}
	return (TRUE);
}
