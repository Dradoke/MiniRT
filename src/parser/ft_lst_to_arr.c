#include "minirt.h"

static void	compute_transform_matrices(t_node *node, t_mat4 *trans_m,
				t_mat4 *rot_m, t_mat4 *scale_m)
{
	t_vec3	scale_vec;
	t_vec3	trans_vec;
	t_f32	r;
	t_f32	h;

	if (node->type == C)
		trans_vec = node->u_data.cam.location;
	else
		trans_vec = node->u_data.sphere.location;
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

static void	get_rotation_matrix(t_node *node, t_mat4 *rot_m)
{
	t_vec3	dir;
	t_mat4	rot_y;
	t_mat4	rot_x;

	mat4_identity(rot_m);
	if (node->type == C)
	{
		dir = vec3_normalize(node->u_data.cam.direction);
		mat4_rotation_y(&rot_y, atan2(dir.x, dir.z));
		mat4_rotation_axis(&rot_x, (t_vec3){{1, 0, 0}}, -asin(dir.y));
		mat4_multiply(rot_m, rot_y, rot_x);
	}
}

static void	build_transform(t_node *node, t_mat4 *out_transform,
				t_mat4 *out_inv_transform)
{
	t_mat4	trans_m;
	t_mat4	rot_m;
	t_mat4	scale_m;
	t_mat4	inv_trans_m;
	t_mat4	inv_scale_m;
	t_vec3	loc;

	compute_transform_matrices(node, &trans_m, &rot_m, &scale_m);
	get_rotation_matrix(node, &rot_m);
	if (node->type == C)
		loc = node->u_data.cam.location;
	else
		loc = node->u_data.sphere.location;
	mat4_translation(&inv_trans_m, (t_vec3){{
		-loc.x,
		-loc.y,
		-loc.z}});
	mat4_scaling(&inv_scale_m, (t_vec3){{
		1.0f / scale_m[0][0],
		1.0f / scale_m[1][1],
		1.0f / scale_m[2][2]}});
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

	scene->mesh[i].type = node->type;
	ft_memcpy(&scene->mesh[i].u_data, &node->u_data,
		sizeof(scene->mesh[i].u_data));
	i++;
}

t_bool	ft_lst_to_arr(t_data *data)
{
	t_list	*lst;
	t_node	*node;
	t_scene	*scene;
	t_vec3	dir;

	scene = &data->scene;
	lst = data->parse_list;
	scene->light = ft_calloc(scene->obj_count[LIGHT] * sizeof(t_point_light));
	scene->mesh = ft_calloc(scene->obj_count[MESH] * sizeof(t_mesh));
	while (lst)
	{
		node = lst->content;
		if (node->type == A)
			scene->ambient_light = node->u_data.ambient_light;
		if (node->type == C)
		{
			scene->cam = node->u_data.cam;
			build_transform(node, &scene->cam.matrix[NORMAL],
				&scene->cam.matrix[INVERTED]);
			dir = vec3_normalize(node->u_data.cam.direction);
			scene->cam.direction.x = -asin(dir.y);
			scene->cam.direction.y = atan2(dir.x, dir.z);
			scene->cam.direction.z = 0;
		}
		if (node->type == L)
			add_light(node, scene);
		if (node->type >= SP && node->type <= TR)
			add_mesh(node, scene);
		lst = lst->next;
	}
	return (TRUE);
}
