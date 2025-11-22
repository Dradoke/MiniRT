#include "minirt.h"
#include <string.h>

void	mat4_identity(t_mat4 *out)
{
	ft_bzero(out, sizeof(t_mat4));
	(*out)[0][0] = 1.0f;
	(*out)[1][1] = 1.0f;
	(*out)[2][2] = 1.0f;
	(*out)[3][3] = 1.0f;
}

void	mat4_translation(t_mat4 *out, t_vec3 v)
{
	mat4_identity(out);
	(*out)[0][3] = v.x;
	(*out)[1][3] = v.y;
	(*out)[2][3] = v.z;
}

void	mat4_scaling(t_mat4 *out, t_vec3 v)
{
	mat4_identity(out);
	(*out)[0][0] = v.x;
	(*out)[1][1] = v.y;
	(*out)[2][2] = v.z;
}

void	mat4_multiply(t_mat4 *out, const t_mat4 a, const t_mat4 b)
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
			result[i][j] = a[i][0] * b[0][j]
				+ a[i][1] * b[1][j]
				+ a[i][2] * b[2][j]
				+ a[i][3] * b[3][j];
			j++;
		}
		i++;
	}
	memcpy(*out, result, sizeof(t_mat4));
}

void	mat4_look_at(t_mat4 *out, t_vec3 from, t_vec3 to, t_vec3 up_temp)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = vec3_normalize(vec3_sub(to, from));
	right = vec3_normalize(vec3_cross(up_temp, forward));
	up = vec3_cross(forward, right);
	mat4_identity(out);
	(*out)[0][0] = right.x;
	(*out)[0][1] = up.x;
	(*out)[0][2] = forward.x;
	(*out)[0][3] = from.x;
	(*out)[1][0] = right.y;
	(*out)[1][1] = up.y;
	(*out)[1][2] = forward.y;
	(*out)[1][3] = from.y;
	(*out)[2][0] = right.z;
	(*out)[2][1] = up.z;
	(*out)[2][2] = forward.z;
	(*out)[2][3] = from.z;
}
