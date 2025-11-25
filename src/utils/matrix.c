#include "minirt.h"
#include <string.h>

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
