#include "minirt.h"

t_vec3	mat4_mult_point(t_mat4 m, t_vec3 v)
{
	t_vec3	result;
	t_f32	w;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];
	if (w != 0.0f && w != 1.0f)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return (result);
}

t_vec3	mat4_mult_vector(t_mat4 m, t_vec3 v)
{
	t_vec3	result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
	return (result);
}
