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
