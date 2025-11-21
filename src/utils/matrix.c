#include "minirt.h"

t_mat4	mat4_identity(void)
{
	t_mat4	m;

	ft_bzero(&m, sizeof(t_mat4));
	m.m[0][0] = 1.0f;
	m.m[1][1] = 1.0f;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

t_mat4	mat4_translation(t_vec3 v)
{
	t_mat4	m;

	m = mat4_identity();
	m.m[0][3] = v.x;
	m.m[1][3] = v.y;
	m.m[2][3] = v.z;
	return (m);
}

t_mat4	mat4_scaling(t_vec3 v)
{
	t_mat4	m;

	m = mat4_identity();
	m.m[0][0] = v.x;
	m.m[1][1] = v.y;
	m.m[2][2] = v.z;
	return (m);
}

t_mat4	mat4_multiply(t_mat4 a, t_mat4 b)
{
	t_mat4	result;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = a.m[i][0] * b.m[0][j]
				+ a.m[i][1] * b.m[1][j]
				+ a.m[i][2] * b.m[2][j]
				+ a.m[i][3] * b.m[3][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_mat4	mat4_look_at(t_vec3 from, t_vec3 to, t_vec3 up_temp)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_mat4	cam_to_world;

	forward = vec3_normalize(vec3_sub(to, from));
	right = vec3_normalize(vec3_cross(up_temp, forward));
	up = vec3_cross(forward, right);
	cam_to_world = mat4_identity();
	cam_to_world.m[0][0] = right.x;
	cam_to_world.m[0][1] = up.x;
	cam_to_world.m[0][2] = forward.x;
	cam_to_world.m[0][3] = from.x;
	cam_to_world.m[1][0] = right.y;
	cam_to_world.m[1][1] = up.y;
	cam_to_world.m[1][2] = forward.y;
	cam_to_world.m[1][3] = from.y;
	cam_to_world.m[2][0] = right.z;
	cam_to_world.m[2][1] = up.z;
	cam_to_world.m[2][2] = forward.z;
	cam_to_world.m[2][3] = from.z;
	return (cam_to_world);
}
