#include "minirt.h"

void	mat4_identity(t_mat4 *out)
{
	t_i32	i;
	t_i32	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				(*out)[i][j] = 1.0f;
			else
				(*out)[i][j] = 0.0f;
			j++;
		}
		i++;
	}
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

void    mat4_multiply(t_mat4 *out, const t_mat4 a, const t_mat4 b)
{
    t_mat4    result;
    int        i;
    int        j;

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

void	mat4_rotation_y(t_mat4 *out, t_f32 angle)
{
	t_f32	c;
	t_f32	s;

	mat4_identity(out);
	c = cos(angle);
	s = sin(angle);
	(*out)[0][0] = c;
	(*out)[0][2] = s;
	(*out)[2][0] = -s;
	(*out)[2][2] = c;
}

void	mat4_rotation_axis(t_mat4 *out, t_vec3 axis, t_f32 angle)
{
	t_f32	c;
	t_f32	s;
	t_f32	t;

	mat4_identity(out);
	axis = vec3_normalize(axis);
	c = cos(angle);
	s = sin(angle);
	t = 1.0f - c;
	(*out)[0][0] = t * axis.x * axis.x + c;
	(*out)[0][1] = t * axis.x * axis.y - s * axis.z;
	(*out)[0][2] = t * axis.x * axis.z + s * axis.y;
	(*out)[1][0] = t * axis.x * axis.y + s * axis.z;
	(*out)[1][1] = t * axis.y * axis.y + c;
	(*out)[1][2] = t * axis.y * axis.z - s * axis.x;
	(*out)[2][0] = t * axis.x * axis.z - s * axis.y;
	(*out)[2][1] = t * axis.y * axis.z + s * axis.x;
	(*out)[2][2] = t * axis.z * axis.z + c;
}

void	mat4_extract_position(t_vec3 *out, const t_mat4 m)
{
	out->x = m[0][3];
	out->y = m[1][3];
	out->z = m[2][3];
}

void	mat4_set_position(t_mat4 *out, t_vec3 pos)
{
	(*out)[0][3] = pos.x;
	(*out)[1][3] = pos.y;
	(*out)[2][3] = pos.z;
}
