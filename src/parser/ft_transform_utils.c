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

static void	compute_inverse_matrices(t_mat4 *scale_m, t_vec3 loc,
				t_mat4 *inv_trans_m, t_mat4 *inv_scale_m)
{
	mat4_translation(inv_trans_m, (t_vec3){{-loc.x, -loc.y, -loc.z}});
	mat4_scaling(inv_scale_m, (t_vec3){{
		1.0f / (*scale_m)[0][0],
		1.0f / (*scale_m)[1][1],
		1.0f / (*scale_m)[2][2]}});
}

void	build_transform(t_node *node, t_mat4 *out_transform,
			t_mat4 *out_inv_transform)
{
	t_mat4	trans_m;
	t_mat4	rot_m;
	t_mat4	scale_m;
	t_mat4	inv_trans_m;
	t_mat4	inv_scale_m;

	compute_transform_matrices(node, &trans_m, &rot_m, &scale_m);
	get_rotation_matrix(node, &rot_m);
	if (node->type == C)
		compute_inverse_matrices(&scale_m, node->u_data.cam.location,
			&inv_trans_m, &inv_scale_m);
	else
		compute_inverse_matrices(&scale_m, node->u_data.sphere.location,
			&inv_trans_m, &inv_scale_m);
	mat4_multiply(out_transform, rot_m, scale_m);
	mat4_multiply(out_transform, trans_m, *out_transform);
	mat4_multiply(out_inv_transform, rot_m, inv_trans_m);
	mat4_multiply(out_inv_transform, inv_scale_m, *out_inv_transform);
}
